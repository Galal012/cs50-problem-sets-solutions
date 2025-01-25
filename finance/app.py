import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

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
    stock = db.execute("SELECT symbol, shares FROM stock WHERE user_id = ?;", session["user_id"])
    total = 0
    for item in stock:
        price = lookup(item["symbol"])["price"]
        item["price"] = price
        item["total"] = item["shares"] * price
        total += item["total"]
    row = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    if len(row) == 0:
        current_cash = 0
    else:
        current_cash = row[0]["cash"]
    return render_template("index.html", stock=stock, cash=current_cash, total=total+current_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    symbol = request.form.get("symbol")
    quote_data = lookup(symbol)
    if not symbol:
        return apology("Missing symbol")
    if not quote_data:
        return apology("Invalid symbol")

    try:
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("Invalid number of shares")
    except ValueError:
        return apology("Shares must be a positive integer")

    current_cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]["cash"]
    if shares*quote_data["price"] > current_cash:
        return apology("No enough cash")

    now = datetime.now()
    date = now.strftime("%Y-%m-%d")
    time = now.strftime("%H:%M:%S")

    db.execute("INSERT INTO history (user_id, symbol, price, shares, transaction_type, date, time) VALUES (?, ?, ?, ?, ?, ?, ?);",
               session["user_id"], quote_data["symbol"], quote_data["price"], shares, "Buy", date, time)

    row = db.execute("SELECT * FROM stock WHERE user_id = ? AND symbol = ?;",
                     session["user_id"], quote_data["symbol"])
    if len(row) != 0:
        db.execute("UPDATE stock SET shares = shares + ? WHERE user_id = ? AND symbol = ?;",
                   shares, session["user_id"], quote_data["symbol"])
    else:
        db.execute("INSERT INTO stock (user_id, symbol, shares) VALUES (?, ?, ?);",
                   session["user_id"], quote_data["symbol"], shares)

    db.execute("UPDATE users SET cash = cash - ? WHERE id = ?;",
               shares*quote_data["price"], session["user_id"])

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute(
        "SELECT transaction_type, symbol, price, shares, date, time FROM history WHERE user_id = ?;", session["user_id"])
    return render_template("history.html", history=history)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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

    symbol = request.form.get("symbol")
    quote_data = lookup(symbol)

    if not quote_data:
        return apology("Invalid stock symbol")
    return render_template("quoted.html", data=quote_data)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if not username:
        return apology("Missing Username")
    if not password:
        return apology("Missing Password")
    if not confirmation:
        return apology("Missing Confirmation")

    rows = db.execute("SELECT * FROM users WHERE username = ?", username)
    if len(rows) > 0:
        return apology("Username already exists!")

    if password != confirmation:
        return apology("Password doesn't match")

    db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
               username, generate_password_hash(password))

    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        stocks = db.execute("SELECT symbol FROM stock WHERE user_id = ?;", session["user_id"])
        return render_template("sell.html", stocks=stocks)

    symbol = str(request.form.get("symbol"))
    quote_data = lookup(symbol)
    if not symbol:
        return apology("Missing symbol")
    if not quote_data:
        return apology("Invalid symbol")

    shares = int(request.form.get("shares"))
    if shares < 1:
        return apology("Invalid number of shares")

    row = db.execute("SELECT shares FROM stock WHERE user_id = ? AND symbol = ?;",
                     session["user_id"], quote_data["symbol"])
    if len(row) == 0:
        owned_shares = 0
    else:
        owned_shares = row[0]["shares"]

    if shares > owned_shares:
        return apology("No enough shares")

    now = datetime.now()
    date = now.strftime("%Y-%m-%d")
    time = now.strftime("%H:%M:%S")

    db.execute("INSERT INTO history (user_id, symbol, price, shares, transaction_type, date, time) VALUES (?, ?, ?, ?, ?, ?, ?);",
               session["user_id"], quote_data["symbol"], quote_data["price"], shares, "Sell", date, time)
    db.execute("UPDATE stock SET shares = shares - ? WHERE user_id = ? AND symbol = ?;",
               shares, session["user_id"], quote_data["symbol"])
    db.execute("DELETE FROM stock WHERE shares = 0;")
    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?;",
               shares*quote_data["price"], session["user_id"])

    return redirect("/")


@app.route("/changePassword", methods=["GET", "POST"])
@login_required
def changePassword():
    """Change the Password."""
    if request.method == "GET":
        return render_template("changePassword.html")

    old_password = request.form.get("old_password")
    new_password = request.form.get("new_password")
    confirmation = request.form.get("confirmation")

    if not old_password or not new_password or not confirmation:
        return apology("Missing Password!")

    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    if not check_password_hash(rows[0]["hash"], old_password):
        return apology("Wrong Password")

    if new_password != confirmation:
        return apology("Password doesn't match")

    db.execute("UPDATE users SET hash = ? WHERE id = ?;",
               generate_password_hash(new_password), session["user_id"])

    return redirect("/")
