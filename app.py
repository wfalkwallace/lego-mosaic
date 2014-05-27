import os
from flask import Flask
from flask import request
from flask import render_template
from flask import redirect
from flask import url_for
from flask import send_from_directory
from werkzeug.utils import secure_filename

app = Flask(__name__)
# image uploading settings
UPLOAD_FOLDER = '/vagrant/uploads'
ALLOWED_EXTENSIONS = set(['png', 'PNG', 'jpg', 'JPG', 'jpeg', 'JPEG', 'gif', 'GIF'])

# disable this for launch (~~ 'watch')
app.config["DEBUG"] = True
# set app-wide uploads folder
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER


# ---------------------------------------------------------------------------- #
#                  _____   ____  _    _ _______ ______  _____                  #
#                 |  __ \ / __ \| |  | |__   __|  ____|/ ____|                 #
#                 | |__) | |  | | |  | |  | |  | |__  | (___                   #
#                 |  _  /| |  | | |  | |  | |  |  __|  \___ \                  #
#                 | | \ \| |__| | |__| |  | |  | |____ ____) |                 #
#                 |_|  \_\\____/ \____/   |_|  |______|_____/                  #
#                                                                              #                           
# ---------------------------------------------------------------------------- #


@app.route("/")
def hello():
  return render_template("index.html")

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_file_extension(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            return redirect(url_for('uploaded_file', filename=filename))
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form action="" method=post enctype=multipart/form-data>
      <p><input type=file name=file>
         <input type=submit value=Upload>
    </form>
    '''

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)


# ---------------------------------------------------------------------------- #
#               _    _ ______ _      _____  ______ _____   _____               #
#              | |  | |  ____| |    |  __ \|  ____|  __ \ / ____|              #
#              | |__| | |__  | |    | |__) | |__  | |__) | (___                #
#              |  __  |  __| | |    |  ___/|  __| |  _  / \___ \               #
#              | |  | | |____| |____| |    | |____| | \ \ ____) |              #
#              |_|  |_|______|______|_|    |______|_|  \_\_____/               #
#                                                                              #
# ---------------------------------------------------------------------------- #


def allowed_file_extension(filename):
    return '.' in filename and filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS


# ---------------------------------------------------------------------------- #
#                  _____  _____     _____ _______ _    _ ______ ______         #
#            /\   |  __ \|  __ \   / ____|__   __| |  | |  ____|  ____|        #
#           /  \  | |__) | |__) | | (___    | |  | |  | | |__  | |__           #
#          / /\ \ |  ___/|  ___/   \___ \   | |  | |  | |  __| |  __|          #
#         / ____ \| |    | |       ____) |  | |  | |__| | |    | |             #
#        /_/    \_\_|    |_|      |_____/   |_|   \____/|_|    |_|             #
#                                                                              #
# ---------------------------------------------------------------------------- #


@app.errorhandler(404)
def page_not_found(error):
    return render_template("404.html"), 404

if __name__ == "__main__":
	app.run(host="0.0.0.0")