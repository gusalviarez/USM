from datetime import datetime, timedelta

def calcular_fecha_especial(fecha_inicial, dia_semana, numero_coincidencias, dia_mes):

    coincidencias_encontradas = 0
    fecha_actual = fecha_inicial
    while coincidencias_encontradas < numero_coincidencias:
        if fecha_actual.weekday() == dia_semana and fecha_actual.day == dia_mes:
            coincidencias_encontradas += 1
        fecha_actual += timedelta(days=1)
        respuesta = fecha_actual - timedelta(days=1)
    return respuesta.strftime("%d/%m/%Y")

# definimos la fecha actual 4/3/2024
fecha_hoy = datetime.today()

# calculamos las fechas que nos piden
print(f"Décimo tercer martes 13: {calcular_fecha_especial(fecha_hoy, 1, 13, 13)}")
print(f"Vigésimo novena vez que se combina el día viernes 20: {calcular_fecha_especial(fecha_hoy, 4, 29, 20)}")
print(f"Sexagésima vez que se combina el sábado 21: {calcular_fecha_especial(fecha_hoy, 5, 60, 21)}")
