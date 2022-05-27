# Set base image (host OS)
FROM ubuntu:18.04

# By default, listen on port 5000
EXPOSE 5000/tcp
# Set the working directory in the container
WORKDIR /app

RUN apt-get update && apt-get upgrade -y && apt-get clean

# Python package management and basic dependencies
RUN apt-get install -y curl python3.7 python3.7-dev python3.7-distutils

# Register the version in alternatives
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3.7 1

# Set python 3 as the default python
RUN update-alternatives --set python /usr/bin/python3.7

# Upgrade pip to latest version
RUN curl -s https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python get-pip.py --force-reinstall && \
    rm get-pip.py

RUN apt-get install build-essential -y --no-install-recommends
RUN apt-get update && apt-get -y install cmake protobuf-compiler

RUN apt-get update && apt-get install -y \
    python3-pip

RUN \ 
    pip3 install --no-cache-dir Cython

RUN apt-get install cython -y
RUN pip3 install Cython

# Copy the dependencies file to the working directory
COPY requirements.txt .

# Install any dependencies
RUN pip3 install -r requirements.txt

RUN apt-get install python3-setuptools -y

ADD bot bot

ADD engine engine

RUN ls

RUN cd engine && ls

COPY __init__.py .

RUN python3 -m pip install --upgrade cython

COPY compile.sh .

RUN chmod +x compile.sh
RUN sh compile.sh

# Copy the content of the local src directory to the working directory
COPY app.py .

RUN ls engine/python

RUN pip3 install flask

# Specify the command to run on container start
CMD ["python", "./app.py"]