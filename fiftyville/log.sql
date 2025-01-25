-- Display all available tables
.tables

-- Display the columns of crime_scene_reports table
.schema crime_scene_reports

-- SELECT the description of the crime occured
SELECT description FROM crime_scene_reports
   WHERE year = 2023
   AND month = 7
   AND day = 28
   AND street = 'Humphrey Street';

-- Display the columns of interviews table
.schema interviews

-- SELECT transcripts that mentions the bakery at the time of the crime from interviews table
SELECT transcript FROM interviews
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND transcript LIKE '%bakery%';

-- Display the columns of bakery_security_logs table
.schema bakery_security_logs

-- SELECT license_plates of suspected cars according to the first transcript
SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
    AND activity = 'exit';

-- Display the columns of people table
.schema people

-- SELECT ids of suspected people using their license_plates
SELECT id FROM people
    WHERE license_plate IN
    (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
        AND activity = 'exit'
    );

-- Display the columns of bank_accounts table
.schema bank_accounts

-- SELECT account_numbers of suspected people using their ids
SELECT account_number FROM bank_accounts
    WHERE person_id IN
    (
        SELECT id FROM people
        WHERE license_plate IN
        (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND minute <= 25
            AND activity = 'exit'
        )
    );

-- Display the columns of atm_transactions table
.schema atm_transactions

-- SELECT account_numbers with a transaction_type = 'withdraw' from suspected people
-- and exclude the others according to the second transcript
SELECT account_number FROM atm_transactions
    WHERE account_number IN
    (
        SELECT account_number FROM bank_accounts
        WHERE person_id IN
        (
            SELECT id FROM people
            WHERE license_plate IN
            (
                SELECT license_plate FROM bakery_security_logs
                WHERE year = 2023
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute >= 15
                AND minute <= 25
                AND activity = 'exit'
            )
        )
    )
    AND year = 2023
    AND month = 7
    AND day = 28
    AND transaction_type = 'withdraw';

-- Display the information of the remaining suspected people
SELECT * FROM people
    WHERE id IN
    (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN
        (
            SELECT account_number FROM atm_transactions
            WHERE account_number IN
            (
                SELECT account_number FROM bank_accounts
                WHERE person_id IN
                (
                    SELECT id FROM people
                    WHERE license_plate IN
                    (
                        SELECT license_plate FROM bakery_security_logs
                        WHERE year = 2023
                        AND month = 7
                        AND day = 28
                        AND hour = 10
                        AND minute >= 15
                        AND minute <= 25
                        AND activity = 'exit'
                    )
                )
            )
            AND year = 2023
            AND month = 7
            AND day = 28
            AND transaction_type = 'withdraw'
        )
    );

-- Display the columns of phone_calls table
.schema phone_calls

-- Check calls of suspected people and exclude ones who didn't make a call for less than a minute
-- according to the third transcript

-- Excluded (no calls)
SELECT caller, receiver, duration FROM phone_calls
    WHERE caller = '(829) 555-5269'
    AND year = 2023
    AND month = 7
    AND day = 28;

-- Excluded (no calls)
SELECT caller, receiver, duration FROM phone_calls
    WHERE caller = '(389) 555-5198'
    AND year = 2023
    AND month = 7
    AND day = 28;

-- Included
SELECT caller, receiver, duration FROM phone_calls
    WHERE caller = '(770) 555-1861'
    AND year = 2023
    AND month = 7
    AND day = 28;

-- Included
SELECT caller, receiver, duration FROM phone_calls
    WHERE caller = '(367) 555-5533'
    AND year = 2023
    AND month = 7
    AND day = 28;

-- Display the columns of airports table
.schema airports

-- SELECT the id of the airport that is placed at Fiftyville
SELECT id FROM airports
    WHERE city = 'Fiftyville';

-- Display the columns of flights table
.schema flights

-- SELECT the first flight going out from Fiftyville on the next day of the crime
-- according the third transcript
SELECT id, origin_airport_id, destination_airport_id FROM flights
    WHERE origin_airport_id = 8
    AND year = 2023
    AND month = 7
    AND day = 29
    ORDER BY hour, minute
    LIMIT 1;

-- Display the columns of passengers table
.schema passengers

-- SELECT the passport_number of the passengers on the selected flight
-- Exclude the person who in not on this flight
-- The other one is the thief
SELECT passport_number FROM passengers
    WHERE flight_id = 36;

-- SELECT the name of the thief
SELECT name FROM people
    WHERE passport_number = '5773159633';

-- SELECT the name of the ACCOMPLICE (the one the has called)
SELECT name FROM people
    WHERE phone_number = '(375) 555-8161';

-- SELECT the city the thief escaped to (the destination city of the flight)
SELECT city FROM airports
    WHERE id = 4;
