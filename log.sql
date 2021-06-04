-- First take a look at the description of the crime.
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2020 AND street = "Chamberlin Street";

-- Check the descriptions given by the witnesses during the interviews.
SELECT name, transcript FROM interviews
WHERE month = 7 AND day = 28 AND year = 2020;

-- Check the caller and receiver from phone calls to identify suspects
SELECT caller, receiver FROM phone_calls
WHERE duration < 60 AND year = 2020 AND month = 7 AND day = 28;

-- Identify names of suspects (theif and accomplice) from phone numbers
-- For thief:
SELECT name, phone_number FROM people
WHERE phone_number IN ("(130) 555-0289", "(499) 555-9472", "(367) 555-5533", "(286) 555-6063", "(770) 555-1861", "(031) 555-6622", "(826) 555-1652", "(338) 555-6650");
-- For accomplice:
SELECT name, phone_number FROM people
WHERE phone_number IN ("(996) 555-8899", "(892) 555-8872", "(375) 555-8161", "(717) 555-1342", "(676) 555-6554", "(725) 555-3243", "(910) 555-3251", "(066) 555-9701", "(704) 555-2131");

-- Identify license plate of thief's car.
SELECT license_plate, minute, activity FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;

-- Finding people with corresponding license plates.
SELECT license_plate, name FROM people
WHERE license_plate IN ("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");

-- Finding people who withdrew money from the banmk on Fifer street before 10:15 am.
SELECT account_number, transaction_type, amount FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- Finding names of the people who withdrew money, using account numbers.
SELECT name FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199));

-- Finding all fligths on July 29, 2020 from fiftyville:
SELECT flights.origin_airport_id, airports.city, airports.full_name FROM airports
JOIN flights ON flights.origin_airport_id = airports.id
WHERE airports.city = "Fiftyville";

-- Finding all flights from fiftyville on July 29, 2020:
SELECT id, destination_airport_id, hour, minute FROM flights
WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = 8
ORDER BY hour, minute;

-- Finding through which flight did the thief and accomplice escape.
-- Checking for Russell - Philip pair
SELECT flight_id FROM passengers
WHERE passport_number IN (SELECT passport_number FROM people WHERE name = "Russell");
-- Checking for Ernest - Berthold pair
SELECT flight_id FROM passengers
WHERE passport_number IN (SELECT passport_number FROM people WHERE name = "Ernest");

-- Finding destination airport.
SELECT city FROM airports
WHERE id = 4;