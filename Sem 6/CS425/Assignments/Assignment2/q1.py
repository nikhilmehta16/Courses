import pandas as pd
import numpy as np
import plotly.express as px
from sklearn.linear_model import LinearRegression as lin_reg


# read and clean data
df = pd.read_excel('./wifi_data.xlsx')
df = df.drop(columns = ['Unnamed: 0'])
df = df.iloc[0:8]

data_points = []
for i in range(df.shape[0]):
    for direction in ['L','R','U','D']:
        data_point = (np.log10(df['Distance (in m)'].iloc[i]), df[direction].iloc[i])
        data_points.append(data_point)

X = [i for (i,j) in data_points]
y = [j for (i,j) in data_points]

# run linear regression
X_np = np.array(X).reshape(-1,1)
reg = lin_reg().fit(X_np,y)
m, c = reg.coef_[0], reg.intercept_
# print(m, c)

# plot results
fig = px.scatter(x=X, y=y)
fig.add_shape(type="line",
    x0=X[0], y0=m*X[0] + c, x1=X[-1], y1=m*X[-1]+c,
    line=dict(
        color="LightSeaGreen",
        width=4,
        dash="dashdot",
    )
)

fig.update_layout(
    title={
        'text': "Log-distance vs. RSSI",
        'y' : 0.98,
        'x' : 0.5,
        'xanchor': 'center',
        'yanchor': 'top'},
    xaxis_title="log-distance",
    yaxis_title="RSSI (in dBm)",
    font=dict(
        family="Courier New, monospace",
        size=18,
        color="RebeccaPurple"
    )
)

fig.show()
print(f"Path loss exponent is {-m/10:0.6f}")

# compute variance wrt best fit line.
y_out = m*X_np + c
variance = 1/(len(y_out)-1) * np.sum((y_out - np.array(y).reshape(-1,1))**2)
print(f"Variance w.r.t best fit line is {variance:0.3f}")

'''
output : 
Path loss exponent is 3.512307
Variance w.r.t best fit line is 9.037
'''