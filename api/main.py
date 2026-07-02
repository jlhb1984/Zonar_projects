from fastapi import FastAPI, UploadFile
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

app = FastAPI()

@app.get("/")
def read_root():
    return {"Hello": "World"}

"""
@app.delete("/items/{item_id}")
def delete_item(item_id: int):
    return {"item_id": item_id, "status": "deleted"}
"""
@app.post("/Linear regression")
async def linear_regression(file: UploadFile):
    df= pd.read_csv(file.file)
    from sklearn.linear_model import LinearRegression
    X = df[["n code"]]
    y = df["gallons"]*3.78541
    model = LinearRegression()
    model.fit(X, y)
    return {"status": "regression created", "intercept": model.intercept_, "coefficient": model.coef_[0]}

@app.post("/Fuel calamp analysis")
async def upload_excel_calamp(file: UploadFile):
    df= pd.read_excel(file.file, engine='openpyxl')
    e0x=df[df["Status"].str.contains('3E0')]
    row_number=e0x.shape[0]

    fs01_dec_value=[]
    fs02_dec_value=[]
    last_index_fs01=[]
    last_index_fs02=[]
    date_fs01_dec_value=[]
    date_fs02_dec_value=[]
    values_dates_fs01=pd.DataFrame()
    values_dates_fs02=pd.DataFrame()

    for i in range(0,row_number):
        e0x_aux=e0x.iloc[i,2]
        aux=e0x_aux.find('3E01')    
        if len(e0x_aux)>0:
            fs01=(e0x_aux[aux:aux+18])
            if len(fs01)>17:
                msb=fs01[10:12]
                lsb=fs01[8:10]
                measure=msb+lsb
                fs01_dec_value.append(int(measure,16))
                date_fs01_dec_value.append(e0x.iloc[i,0])            
                msb=fs01[28:30]
                lsb=fs01[26:28]
                fs01_dec_value.append(int(measure,16))
                date_fs01_dec_value.append(e0x.iloc[i,0]) 
                msb=fs01[46:48]
                lsb=fs01[44:46]
                fs01_dec_value.append(int(measure,16))
                date_fs01_dec_value.append(e0x.iloc[i,0])
                msb=fs01[46:48]
                lsb=fs01[44:46]
                fs01_dec_value.append(int(measure,16))
                date_fs01_dec_value.append(e0x.iloc[i,0])
                msb=fs01[64:66]
                lsb=fs01[62:64]
                last_index_fs01=i        
                
    #print(i, raw_fuel_data.iloc[i,0] )

    for i in range(0,row_number):
        e0x_aux=e0x.iloc[i,2]
        aux=e0x_aux.find('3E02')
        if len(e0x_aux)>0:
            fs02=e0x_aux[aux:aux+18]
            if len(fs02)>17:
                msb=fs02[10:12]
                lsb=fs02[8:10]
                measure=msb+lsb
                fs02_dec_value.append(int(measure,16))
                date_fs02_dec_value.append(e0x.iloc[i,0])            
                msb=fs02[28:30]
                lsb=fs02[26:28]
                fs02_dec_value.append(int(measure,16))
                date_fs02_dec_value.append(e0x.iloc[i,0]) 
                msb=fs02[46:48]
                lsb=fs02[44:46]
                fs02_dec_value.append(int(measure,16))
                date_fs02_dec_value.append(e0x.iloc[i,0])
                msb=fs02[46:48]
                lsb=fs02[44:46]
                fs02_dec_value.append(int(measure,16))
                date_fs02_dec_value.append(e0x.iloc[i,0])
                msb=fs02[64:66]
                lsb=fs02[62:64]
                #last_index_fs02=i        
                
            #print(fs01_cad)   

    fs01_count=len(fs01_dec_value)
    fs02_count=len(fs02_dec_value)
    values_dates_fs01['Value fs01']=fs01_dec_value
    values_dates_fs01['Dates fs01']=date_fs01_dec_value
    values_dates_fs02['Value fs02']=fs02_dec_value
    values_dates_fs02['Dates fs02']=date_fs02_dec_value

    fs01_x_values=[]
    fs02_x_values=[]

    for i in range(0,fs01_count):
        fs01_x_values.append(i)
        
    for i in range(0,fs02_count):
        fs02_x_values.append(i)

    fig, ax = plt.subplots(1,2, figsize=(12, 6))

    ax[0].plot(fs01_x_values,fs01_dec_value)
    ax[1].plot(fs02_x_values,fs02_dec_value)
    plt.show()
    
    return {"rows":len(df), "columns": list(df.columns)}

@app.post("/Fuel heroX analysis")
async def upload_excel_herox(file: UploadFile):
    df= pd.read_excel(file.file, engine='openpyxl')
    e0x=df[df['Status'].str.contains('3E0')]
    row_number=e0x.shape[0]
    fs01_dec_value=[]
    fs02_dec_value=[]
    last_index_fs01=[]
    last_index_fs02=[]
    date_fs01_dec_value=[]
    date_fs02_dec_value=[]
    values_dates_fs01=pd.DataFrame()
    values_dates_fs02=pd.DataFrame()

    for i in range(0,row_number):
        e0x_aux=e0x.iloc[i,2]
        aux=e0x_aux.find('3E01')
        if len(e0x_aux)>0:
            fs01=(e0x_aux[aux:aux+18])
            if len(fs01)>17:
                msb=fs01[10:12]
                lsb=fs01[8:10]
                measure=msb+lsb
                fs01_dec_value.append(int(measure,16))
                date_fs01_dec_value.append(e0x.iloc[i,0])
                last_index_fs01=i    

    for i in range(0,row_number):
        e0x_aux=e0x.iloc[i,2]
        aux=e0x_aux.find('3E02')
        if len(e0x_aux)>0:
            fs02=e0x_aux[aux:aux+18]
            if len(fs02)>17:
                msb=fs02[10:12]
                lsb=fs02[8:10]
                measure=msb+lsb
                fs02_dec_value.append(int(measure,16))
                date_fs02_dec_value.append(e0x.iloc[i,0])
                last_index_fs02=i     

    fs01_count=len(fs01_dec_value)
    fs02_count=len(fs02_dec_value)
    #print('El Ncode en decimal es:')
    values_dates_fs01['value']=fs01_dec_value
    values_dates_fs01['date']=date_fs01_dec_value
    values_dates_fs02['value']=fs02_dec_value
    values_dates_fs02['date']=date_fs02_dec_value

    fs01_x_values=[]
    fs02_x_values=[]

    for i in range(0,fs01_count):
        fs01_x_values.append(i)
        
    for i in range(0,fs02_count):
        fs02_x_values.append(i)

    fig, ax = plt.subplots(1,2, figsize=(12, 6))

    ax[0].plot(fs01_x_values,fs01_dec_value)
    ax[1].plot(fs02_x_values,fs02_dec_value)
    plt.show()
    
    return {"rows":len(df), "columns": list(df.columns)}