from flask import Flask

app = Flask(__name__)

# disable this for launch (~~ 'watch')
app.config["DEBUG"] = True

@app.route("/")
def hello():
	return "hello world!"

@app.route("/name")
def name():
	return "William G. Falk-Wallace"

@app.route("/search/<search_query>")
def search(search_query):
	return search_query

if __name__ == "__main__":
	app.run(host="0.0.0.0")