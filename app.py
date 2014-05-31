import os
import datetime
from flask import Flask
from flask import request
from flask import render_template
from flask import redirect
from flask import url_for
from flask import send_from_directory
from werkzeug.utils import secure_filename
# PIL Pillow imports
from PIL import Image

app = Flask(__name__)
app.config.from_object('config.config')

# image uploading settings
UPLOAD_FOLDER = 'uploads/'
ALLOWED_EXTENSIONS = set([
    'png', 'PNG',
    'jpg', 'JPG',
    'jpeg', 'JPEG',
    'gif', 'GIF'
])

# disable this for launch (~~ 'watch')
app.config["DEBUG"] = True
# set app-wide uploads folder
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
# limit image/upload max size to 16MB
# app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024


# -------------------------------------------------------------------------- #
#                 _____   ____  _    _ _______ ______  _____                 #
#                |  __ \ / __ \| |  | |__   __|  ____|/ ____|                #
#                | |__) | |  | | |  | |  | |  | |__  | (___                  #
#                |  _  /| |  | | |  | |  | |  |  __|  \___ \                 #
#                | | \ \| |__| | |__| |  | |  | |____ ____) |                #
#                |_|  \_\\____/ \____/   |_|  |______|_____/                 #
#                                                                            #
# -------------------------------------------------------------------------- #


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
            return redirect(url_for('mosaic', filename=filename))
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


@app.route('/mosaic/<filename>')
def result(filename):
    start = datetime.datetime.now()

    output_filename = '%s%s.%s' % (filename.rsplit('.', 1)[0], 
                                   "_mosaic", 
                                   filename.rsplit('.', 1)[1]

                                  )

    imagepath = url_for('uploaded_file', filename=filename)
    output_imagepath = url_for('uploaded_file', filename=output_filename)

    filepath = '%s%s' % (app.config['UPLOAD_FOLDER'], filename)
    output_filepath = '%s%s' % (app.config['UPLOAD_FOLDER'], output_filename)

    image = Image.open(filepath)
    size = image.size

    width = size[0]
    height = size[1]

    num_buckets_x = 75
    num_buckets_y = 70

    bucket_size_x = size[0] / num_buckets_x
    bucket_size_y = size[1] / num_buckets_y

    for x in range(0, num_buckets_x):
        for y in range(0, num_buckets_y):

            window_left = x * bucket_size_x
            window_upper = y * bucket_size_y
            window_right = window_left + bucket_size_x
            window_lower = window_upper + bucket_size_y

            window_bounds = (window_left,
                             window_upper,
                             window_right,
                             window_lower
                            )
            window = image.crop(window_bounds)            

            count = avg = 0
            total = (0, 0, 0)
            for window_x in range(0, bucket_size_x):
                for window_y in range(0, bucket_size_y):
                    pixel = window.getpixel((window_x, window_y))
                    total = tuple(map(sum,zip(total,pixel)))
                    count += 1
            avg = tuple(val/count for val in total)
            for window_x in range(0, bucket_size_x):
                for window_y in range(0, bucket_size_y):
                    window.putpixel((window_x, window_y), avg)
            image.paste(window, window_bounds)
    image.save(output_filepath)
    time = datetime.datetime.now() - start
    return render_template("show.html", 
                            filepath=imagepath, 
                            output=output_imagepath,
                            size=size,
                            time=time)


# -------------------------------------------------------------------------- #
#              _    _ ______ _      _____  ______ _____   _____              #
#             | |  | |  ____| |    |  __ \|  ____|  __ \ / ____|             #
#             | |__| | |__  | |    | |__) | |__  | |__) | (___               #
#             |  __  |  __| | |    |  ___/|  __| |  _  / \___ \              #
#             | |  | | |____| |____| |    | |____| | \ \ ____) |             #
#             |_|  |_|______|______|_|    |______|_|  \_\_____/              #
#                                                                            #
# -------------------------------------------------------------------------- #


def allowed_file_extension(filename):
    return '.' in filename and \
        filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS




# -------------------------------------------------------------------------- #
#                 _____  _____     _____ _______ _    _ ______ ______        #
#           /\   |  __ \|  __ \   / ____|__   __| |  | |  ____|  ____|       #
#          /  \  | |__) | |__) | | (___    | |  | |  | | |__  | |__          #
#         / /\ \ |  ___/|  ___/   \___ \   | |  | |  | |  __| |  __|         #
#        / ____ \| |    | |       ____) |  | |  | |__| | |    | |            #
#       /_/    \_\_|    |_|      |_____/   |_|   \____/|_|    |_|            #
#                                                                            #
# -------------------------------------------------------------------------- #


@app.errorhandler(500)
def page_not_found(error):
    return render_template("500.html"), 500


@app.errorhandler(404)
def page_not_found(error):
    return render_template("404.html"), 404


if __name__ == "__main__":
  app.run(host="0.0.0.0")