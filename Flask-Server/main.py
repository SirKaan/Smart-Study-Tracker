from flask import Flask, request, jsonify
import csv;
from datetime import datetime;
import os;

app = Flask(__name__)

#ID's die toegang hebben
USERS = {
    "45A2C133": "Kaan"
}

csvPath = './log/study_log.csv'

#loggen naar csv-file
def log_to_csv(id, name, actie):
    #Controleren of de file bestaat
    fileExists = os.path.exists(csvPath)

    #Bestand openen in append mode
    with open(csvPath, mode='a', newline='') as csvFile:
        writer = csv.writer(csvFile)

        if not fileExists:
            writer.writerow(["DateTime", "Name", "ID", "Action"])

        time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        writer.writerow([time, name, id, actie])


#bepalen of er ingeklokt of uitgeklokt wordt
def clock_in_or_out(id):
    if not os.path.exists(csvPath):
        return "In"

    lastAction = "Out" #Standaard aanname is out: als er nog geen record staat voor het id -> in

    with open(csvPath, mode='r') as bestand:
        reader = csv.DictReader(bestand)
        for record in reader:
            if record['ID'] == id:
                lastAction = record['Action']

    if lastAction == "In":
        return "Out"
    else:
        return "In"


id = "45A2C133"
action = clock_in_or_out(id)
log_to_csv(id, USERS[id], action)

