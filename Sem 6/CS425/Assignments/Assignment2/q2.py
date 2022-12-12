import pandas as pd
import numpy as np

def dbm_to_d(dbm, m = -35.123069779990345 , c = -37.40204328699555):
    log_d = (dbm - c)/m
    d = 10**(log_d)
    return d

df = pd.read_excel('./readings_q2.xlsx')

dbm_list = list(df['RSSI (in dBm)'])
dist_list = list(df['Measured distance(in m)'])
expected_d_list = []
for dbm, actual_distance in zip(dbm_list, dist_list):
    out = dbm_to_d(dbm)
    expected_d_list.append(out)
    print(f"{dbm = }, actual distance = {actual_distance:0.3f} m, expected distance = {out:0.3f} m")

error = np.array(expected_d_list) - np.array(dist_list)
print(f"\nAverage error is {np.mean(error**2):0.3f} sq. meter")