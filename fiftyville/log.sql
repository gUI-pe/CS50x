-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Crime report for the case:
SELECT * FROM crime_scene_reports WHERE month = '7' AND street = 'Humphrey Street' AND day = '28';
--| id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
--+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
--| 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

-- looking into the interviews
SELECT * FROM interviews
WHERE day = '28' AND month = '7'
AND transcript LIKE '%bakery%';
--| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

-- INVESTIGETING what happened in the bakery since 10:15 till 10:25
SELECT * FROM bakery_security_logs WHERE year = '2021' AND month = '7' AND day = '28' AND hour = '10.00' AND minute <= '25' AND minute >= '15';
-- +-----+------+-------+-----+------+--------+----------+---------------+
--| id  | year | month | day | hour | minute | activity | license_plate |
--| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
--| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
--| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
--| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
--| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
--| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
--| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
--| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |

--getting the name of these suspects
SELECT name FROM people
WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = '2021' AND month = '7' AND day = '28' AND hour = '10.00' AND minute <= '25' AND minute >= '15');
--+---------+
--|  name   |
--+---------+
--| Vanessa |
--| Barry   |
--| Iman    |
--| Sofia   |
--| Luca    |
--| Diana   |
--| Kelsey  |
--| Bruce   |
--+---------+
-- following lead num2: Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
SELECT * FROM atm_transactions
WHERE day = '28' AND month = '7'
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
--| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
--| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
--| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
--| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
--| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
--| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
--| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+
--getting the name of lead.2 suspects
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE day = '28' AND month = '7'
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw');
--+---------+
--|  name   |
--+---------+
--| Bruce   |
--| Diana   |
--| Brooke  |
--| Kenny   |
--| Iman    |
--| Luca    |
--| Taylor  |
--| Benista |
--+---------+
-- Compare suspects lists
--+---------+----------+--
--|  name   |   name
--+---------+----------+--
--| Bruce   | Vanessa
--| Diana   | Barry
--| Brooke  | Iman
--| Kenny   | Sofia
--| Iman    | Luca
--| Luca    | Diana
--| Taylor  | Kelsey
--| Benista | Bruce
--+---------+----------+--
--new list of suspects
--+-----+--
-- Bruce
-- Diana
-- Iman
-- Luca
--+-----+--

-- Following lead.3: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
SELECT * FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE duration < '60' AND name IN
('Bruce', 'Diana', 'Iman', 'Luca')
AND day = '28';
--|   id   | name  |  phone_number  | passport_number | license_plate | id  |     caller     |    receiver    | year | month | day | duration |
--+--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |

-- new list of suspects
--+-----+--
-- Bruce
-- Diana
--+-----+--

-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- finding the earliest flight out of Fiftyville
SELECT * FROM flights
WHERE day = '29' AND origin_airport_id = (SELECT id FROM airports WHERE full_name LIKE '%tyville%')
ORDER BY hour;
--this is the eraliest flight
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
--+----+-------------------+------------------------+------+-------+-----+------+--------+

-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- Checking if Bruce or Diana were in that flight (id: 36)
SELECT * FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = '36' AND
(name = 'Bruce' OR name = 'Diana');
--+-----------+-----------------+------+--------+-------+----------------+-----------------+---------------+
--| flight_id | passport_number | seat |   id   | name  |  phone_number  | passport_number | license_plate |
--+-----------+-----------------+------+--------+-------+----------------+-----------------+---------------+
--| 36        | 5773159633      | 4A   | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--+-----------+-----------------+------+--------+-------+----------------+-----------------+---------------+

--updating suspects list
-- BRUCE IS THE ONLY SUSPECT
-- city the thief ESCAPED TO? He escaped to the city of the destination airport which is airport n.4
SELECT full_name FROM airports WHERE id = '4';
--+-------------------+
--|     full_name     |
--+-------------------+
--| LaGuardia Airport |
--+-------------------+
-- LaGuardia Airport is located at New York

-- The ACCOMPLICE is who he called at 28th of july for less than a minute
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
--+--------+
--|  name  |
--+--------+
--| Robin  |
--+--------+
-- PHILIP IS THE ACCOMPLICE