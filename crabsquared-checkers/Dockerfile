FROM node:16
ARG path=~/crabsquared-checkers

RUN mkdir -p $path
WORKDIR $path

RUN apt-get update && apt-get install -y python3

RUN npm install yarn

RUN apt-get install -y python3-pip
RUN python3 -m pip install flask python-dotenv Cython

RUN apt-get install -y cmake
COPY . ~/crabsquared-checkers
WORKDIR ~/crabsquared-checkers
RUN yarn compile
RUN npm install npm-run-all

# TO HEROKU USTAWI!! powinnismy wykrywac nieustawienie portu w node
# ENV PORT=8000
# EXPOSE 5000
#ENTRYPOINT ["npm", "start"]
ENTRYPOINT ["npm-run-all", "-p", "-r", "start-react", "start-api"]
