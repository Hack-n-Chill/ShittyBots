import pandas as pd
import numpy as np
import os

df = pd.read_csv("../Analytics/DB_01.csv")

mask = df[" mask"]
nomask = df[" nomask"]
ratio = df[" ratio"]
time = df[" frame"]