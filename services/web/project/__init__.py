from flask import Flask, jsonify
from flask_sqlalchemy import SQLAlchemy


# __name__ is set to the current class/package by default
# Here, tells flask where to look for the resources, ie. insdie the current package
app = Flask(__name__)

# Load configuration from configuration file for flask
# The configuration is to be found in project/config(.py)/Config(Class)
app.config.from_object("project.config.Config")

# Create a database model
db = SQLAlchemy(app)


class User(db.Model):
    __tablename__ = "users"

    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(128), unique=True, nullable=False)
    active = db.Column(db.Boolean(), default=True, nullable=False)

    def __init__(self, email):
        self.email = email


@app.route("/")
def hello_world():
    return jsonify(hello="world")
