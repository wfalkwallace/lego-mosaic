sudo apt-get update
sudo apt-get install -y python
sudo apt-get install -y python-pip
sudo apt-get install -y vim
sudo pip install flask
sudo apt-get -y build-dep python-imaging
sudo pip install -r /vagrant/requirements.txt
source config/settings.prod

echo hello