import os

from werkzeug.utils import secure_filename
from flask import (
    Flask,
    jsonify,
    send_from_directory,
    request,
    redirect,
    url_for
)
from flask_sqlalchemy import SQLAlchemy


# __name__ is set to the current class/package by default
# Here, tells flask where to look for the resources, ie. inside the current package
app = Flask(__name__)

# Load configuration from configuration file for flask
# The configuration is to be found in project/config(.py)/Config(Class)
app.config.from_object("project.config.Config")

# Create a database model
# In SQLAlchemy, model is independent of the true database behind it.
# Manage database using python language and python model.
# To use existing db: https://zhuanlan.zhihu.com/p/27400862#反射
# More on: https://flask-sqlalchemy.palletsprojects.com/en/2.x/
db = SQLAlchemy(app)


# Example of models: https://flask-sqlalchemy.palletsprojects.com/en/2.x/models/
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


@app.route("/parameters/<name>/<int:userid>")
def learn_parameters(name, userid):
    return "Test with {}, id = {}".format(name, userid)


@app.route("/methods", methods=['GET', 'POST'])
def learn_requests():
    if request.method == 'POST':
        username = request.args.get('username', 'Default')
        if (request.is_json):
            content = request.get_json()
            return content["username"]
        else:
            return "No json data"
        return 'This is a POST request, username = {}'.format(username)
    else:
        return 'This is a GET request'


@app.route("/static/<path:filename>")
def staticfiles(filename):
    return send_from_directory(app.config["STATIC_FOLDER"], filename)


@app.route("/media/<path:filename>")
def mediafiles(filename):
    return send_from_directory(app.config["MEDIA_FOLDER"], filename)


@app.route("/upload", methods=["GET", "POST"])
def upload_file():
    if request.method == "POST":
        file = request.files["file"]
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config["MEDIA_FOLDER"], filename))
    return """
    <!doctype html>
    <title>upload new File</title>
    <form action="" method=post enctype=multipart/form-data>
      <p><input type=file name=file><input type=submit value=Upload>
    </form>
    """
