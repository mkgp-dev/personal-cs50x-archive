import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, get_flashed_messages, request, session
from flask_session import Session
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
    # Grab balance from user
    user_data = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    user_bal = user_data[0]['cash']

    # Grab transactions log from user
    user_trnsct = db.execute(
        "SELECT symbol, SUM(amount) AS total_amount FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_amount > 0", session["user_id"])

    # Make a new list to have an updated stock price
    table = []
    for row in user_trnsct:
        symbol = row['symbol']
        amount = row['total_amount']

        # Re'use lookup
        smbl = lookup(symbol)
        updp = smbl['price']

        total_value = amount * updp

        table.append({
            "symbol": symbol,
            "shares": amount,
            "price": updp,
            "total": total_value,
            "tPrice": usd(updp),
            "tTotal": usd(total_value)
        })

    # Overall total of portfolio and balance
    balance = usd(user_bal)
    table_total = sum(item['total'] for item in table)
    overall_total = usd(int(user_bal) + int(table_total))

    return render_template("portfolio.html", balance=balance, portfolio=overall_total, table=table)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Execute lookup of symbol
        smbl = lookup(symbol)

        if not smbl or 'name' not in smbl:
            return apology("invalid symbol", 400)

        shares = request.form.get("shares")
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("invalid amount of shares", 400)
        except ValueError:
            return apology("invalid amount of shares", 400)

        # Define variables
        stock_price = smbl['price']
        data = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Framework of buying
        if data[0]['cash'] > stock_price:
            in_total = shares * stock_price

            # Throw an error if balance is insufficient
            if in_total > data[0]['cash']:
                return apology('Insufficient balance', 400)

            # Check if symbol exist in user and the same stock price
            trnsct = db.execute(
                "SELECT id, symbol, stock_price FROM transactions WHERE user_id = ?", session["user_id"])

            status = False
            for row in trnsct or []:
                if row['symbol'] == symbol and int(row['stock_price']) == stock_price:
                    try:
                        db.execute("BEGIN TRANSACTION;")

                        db.execute(
                            "UPDATE transactions SET amount = amount + ? WHERE id = ?", shares, row['id'])

                        db.execute("COMMIT;")

                        status = True
                        break
                    except Exception as error:
                        db.execute("ROLLBACK;")
                        return apology(f"An error has occured: {error}", 500)

            if not status:
                # Insert buy transaction to db
                try:
                    db.execute("INSERT INTO transactions (symbol, amount, user_id, stock_price) VALUES (?, ?, ?, ?)",
                               symbol, shares, session["user_id"], stock_price)
                except Exception as error:
                    return apology("An error has occured", 500)

            # Deduct balance to user
            try:
                db.execute("BEGIN TRANSACTION;")

                db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                           in_total, session["user_id"])

                db.execute("COMMIT;")
            except Exception as error:
                db.execute("ROLLBACK;")
                return apology(f"An error has occured: {error}", 500)

            flash(f"You have successfully bought {shares} stocks of {symbol}")

            return redirect('/')

        else:
            return apology("not enough balance", 400)

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    data = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    # Make a new list to apply usd helper, my god.
    table = []
    for row in data:
        table.append({
            "symbol": row['symbol'],
            "shares": row['amount'],
            "price": usd(row['stock_price']),
            "date": row['date_created'],
        })

    return render_template("history.html", table=table)


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
    # Grabbing POST method
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("invalid symbol", 400)

        srch = lookup(symbol)
        if srch and 'name' in srch:

            result = f"<strong>{srch['symbol']}</strong> {srch['name']} cost <u>{usd(srch['price'])}</u>"

            return render_template("quote.html", result=result)
        else:
            return apology("symbol not found", 400)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Session kill
    session.clear()

    if request.method == "POST":
        # Variables
        usrn = request.form.get("username")
        if not usrn:
            return apology("username is missing", 400)
        # elif len(usrn) < 6:
        #    return apology("username should be more than 6 characters", 400)

        passwd = request.form.get("password")
        if not passwd:
            return apology("password is missing", 400)
        # elif len(passwd) < 6:
        #    return apology("password should be more than 6 characters", 400)

        cpasswd = request.form.get("confirmation")
        if not cpasswd:
            return apology("confirm your password", 400)

        if passwd != cpasswd:
            return apology("password is not the same", 400)

        # Hash password
        hashpsswd = generate_password_hash(passwd)

        try:
            # Insert into db
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", usrn, hashpsswd)

            flash('You have successfully registered')

            return redirect("/login")
        except Exception as error:
            if "UNIQUE" in str(error):
                return apology("username already taken", 400)
            else:
                return apology("An error has occured", 500)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_trnsct = db.execute(
        "SELECT symbol, SUM(amount) AS total_amount FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_amount > 0", session["user_id"])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Buy some shares", 400)

        # Execute lookup of symbol
        smbl = lookup(symbol)

        if not smbl or 'name' not in smbl:
            return apology("invalid symbol", 400)

        # Check current shares of user
        shares = request.form.get("shares")

        try:
            shares = int(shares)
        except ValueError:
            return apology("invalid amount", 400)

        for row in user_trnsct:
            if symbol == row['symbol']:
                if int(shares) > int(row['total_amount']):
                    return apology("you have insufficient stocks", 400)

        # Define variables
        stock_price = smbl['price']
        total_sell = shares * stock_price

        # Log sell transaction to db
        try:
            db.execute("INSERT INTO transactions (symbol, amount, user_id, stock_price) VALUES (?, ?, ?, ?)",
                       symbol, -shares, session["user_id"], stock_price)
        except Exception as error:
            return apology("An error has occured", 500)

        # Add balance to user
        try:
            db.execute("BEGIN TRANSACTION;")

            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                       total_sell, session["user_id"])

            db.execute("COMMIT;")
        except Exception as error:
            db.execute("ROLLBACK;")
            return apology(f"An error has occured: {error}", 500)

        flash(f"You have successfully sold {shares} stocks of {symbol}")

        return redirect('/')
    else:
        return render_template("sell.html", options=user_trnsct)


# Personal touch: Change password
@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    """Show history of transactions"""

    data = db.execute("SELECT id, username FROM users WHERE id = ?", session["user_id"])
    idusern = data[0]['id']
    usern = data[0]['username']

    if request.method == "POST":
        id = request.form.get("id")
        passwd = request.form.get("password")
        if not passwd:
            return apology("password is missing", 400)
        # elif len(passwd) < 6:
        #    return apology("password should be more than 6 characters", 400)

        cpasswd = request.form.get("confirmation")
        if not cpasswd:
            return apology("confirm your password", 400)

        if passwd != cpasswd:
            return apology("password is not the same", 400)

        # Hash password
        hashpsswd = generate_password_hash(passwd)

        # Update user password
        try:
            db.execute("BEGIN TRANSACTION;")

            db.execute("UPDATE users SET hash = ? WHERE id = ?", hashpsswd, id)

            db.execute("COMMIT;")

            flash('You have successfully changed your password')

            return redirect("/profile")
        except Exception as error:
            db.execute("ROLLBACK;")
            return apology("An error has occured", 500)
    else:
        return render_template("profile.html", id=idusern, username=usern)
