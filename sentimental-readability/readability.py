from cs50 import get_string


def main():
    text = get_string("Text: ")
    w = words(text)
    s = sentences(text)
    l = letters(text)

    W = w
    S = s / W * 100
    L = l / W * 100

    index = 0.0588 * L - 0.296 * S - 15.8

    Grade = round(index)
    if Grade > 16:
        print("Grade 16+")
    elif Grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {Grade}")


def letters(text):
    letters = 0
    for c in text:
        if c.isalpha():
            letters += 1
    return letters


def words(text):
    words = (text.count(' ') + 1)
    return words


def sentences(text):
    s = 0
    s += text.count('!')
    s += text.count('.')
    s += text.count('?')
    return s


main()