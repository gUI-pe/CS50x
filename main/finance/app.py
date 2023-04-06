import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    stocks = db.execute(
        "SELECT symbol, name, price, SUM(shares) as allshares FROM purchases WHERE user_id = ? GROUP BY symbol", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    grandtotal = cash

    for stock in stocks:
        grandtotal += stock["price"] * stock["allshares"]

    return render_template("index.html", stocks=stocks, cash=usd(cash), grandtotal=grandtotal, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        return render_template("buy.html")

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        info = lookup(symbol)

        if not symbol:
            return apology("Quote symbol needed")
        elif not info:
            return apology("Quote symbol is invalid")

        try:
            shares = int(shares)
        except:
            return apology("Share amount must be a integer!")

        if shares <= 0:
            return apology("Share amount must be a positive integer")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        info_name = info["name"]
        info_price = info["price"]
        holding_price = info["price"] * int(shares)

        if holding_price > cash:
            return apology("Insuficient funds")

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - holding_price, user_id)
        db.execute("INSERT INTO purchases (user_id, name, shares, price, status, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, info_name, int(shares), info_price, "buy", symbol)

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT symbol, status, name, price, shares, time FROM purchases WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Quote symbol needed")
        info = lookup(symbol)
        if not info:
            return apology("Quote symbol is invalid")

        return render_template("quoted.html", info=info)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")

    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif confirmation != password:
            return apology("passwords are not the same!", 400)
        elif len(db.execute("SELECT * FROM users WHERE username = ?", username)) >= 1:
            return apology("username is already taken", 400)

        hashedpassword = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashedpassword)

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        options = db.execute("SELECT symbol FROM purchases WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", options=options)

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        info = lookup(symbol)

        if not symbol:
            return apology("Quote symbol needed")
        elif not info:
            return apology("Quote symbol is invalid")

        try:
            shares = int(shares)
        except:
            return apology("Share amount must be a integer!")

        if shares <= 0:
            return apology("Share amount must be a positive integer")

        selectedshare = db.execute(
            "SELECT SUM(shares) as sha FROM purchases WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["sha"]
        if shares > selectedshare:
            return apology("You don't have (all) these shares")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + (int(shares) * info["price"]), user_id)
        db.execute("INSERT INTO purchases (user_id, name, shares, price, status, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, info["name"], -shares, info["price"], "sell", symbol)

        return redirect("/")


@app.route("/addmoney", methods=["POST"])
@login_required
def addmoney():
    user_id = session["user_id"]
    addmoney = request.form.get("addmoney")

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    if not addmoney:
        return apology("type a number", 400)
    elif int(addmoney) <= 0:
        return apology("type a positive number", 400)
    db.execute("UPDATE users SET cash = ? WHERE id = ?", int(cash) + int(addmoney), user_id)
    return redirect("/")