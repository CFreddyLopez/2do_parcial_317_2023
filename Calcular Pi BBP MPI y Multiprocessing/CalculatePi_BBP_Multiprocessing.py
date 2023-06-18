import multiprocessing
from decimal import Decimal, getcontext

#Formula Bailey Borwien Plouffe BBP
def calculate_bbp(start, end):
    sum = Decimal(0)
    for k in range(start, end):
        numerator = Decimal(1) / Decimal(16) ** k
        denominator1 = Decimal(8) * k + Decimal(1)
        denominator2 = Decimal(8) * k + Decimal(4)
        denominator3 = Decimal(8) * k + Decimal(5)
        denominator4 = Decimal(8) * k + Decimal(6)
        sum += numerator * (Decimal(4) / denominator1 - Decimal(2) / denominator2 - Decimal(1) / denominator3 - Decimal(1) / denominator4)
    return sum


#Calcular Pi usando Multiprocessing
def calculate_pi(num_terms):
    num_processes = multiprocessing.cpu_count()
    pool = multiprocessing.Pool(processes=num_processes)
    chunk_size = num_terms // num_processes
    results = pool.starmap(calculate_bbp, [(i * chunk_size, (i + 1) * chunk_size) for i in range(num_processes)])
    pi = sum(results)
    return pi


if __name__ == '__main__':
    num_terms = int(input("Ingrese el número de términos de Precision menos a 10000: "))
    getcontext().prec = 20  # Establecer la precisión decimal a 20 dígitos
    pi = calculate_pi(num_terms)
    print("El valor aproximado de pi es:", pi)
