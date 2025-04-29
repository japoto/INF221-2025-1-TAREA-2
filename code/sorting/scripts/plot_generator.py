import re
import os
import matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict

def parse_benchmark_file(filename):
    algorithms = ['merge', 'quick', 'selection', 'sort']
    data = defaultdict(lambda: defaultdict(list))
    
    with open(filename, 'r') as file:
        content = file.read()
    
    current_algorithm = None
    
    for line in content.split('\n'):
        if line.startswith('---- '):
            current_algorithm = line.strip('---- ').strip()
            continue
        
        if current_algorithm and line.startswith(current_algorithm):
            parts = re.split(r'\s+->\s+', line)
            if len(parts) < 2:
                continue
                
            file_info = parts[0].split()[1]
            metrics = parts[1].split(' | ')
            
            size = int(file_info.split('_')[0])
            data_type = '_'.join(file_info.split('_')[1:-2])
            distribution = file_info.split('_')[-2]
            
            time = float(metrics[0].split()[0])
            memory = float(metrics[1].split()[0])
            
            key = f"{size}_{data_type}_{distribution}"
            data[current_algorithm][key].append({
                'time': time,
                'memory': memory,
                'size': size,
                'data_type': data_type,
                'distribution': distribution
            })
    
    return data

def create_scaling_plots(data, output_dir):
    """Genera gráficos individuales y uno comparativo"""
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    algorithms = ['merge', 'quick', 'selection', 'sort']
    sizes = [10, 1000, 100000]
    colors = {'merge': 'blue', 'quick': 'green', 'selection': 'red', 'sort': 'purple'}
    
    # Datos para el gráfico comparativo
    all_time_data = {algo: [] for algo in algorithms}
    all_memory_data = {algo: [] for algo in algorithms}
    
    # Gráficos individuales
    for algo in algorithms:
        if algo not in data:
            continue
        
        time_by_size = defaultdict(list)
        memory_by_size = defaultdict(list)
        
        for group in data[algo]:
            entries = data[algo][group]
            size = entries[0]['size']
            avg_time = np.mean([e['time'] for e in entries])
            avg_memory = np.mean([e['memory'] for e in entries])
            
            time_by_size[size].append(avg_time)
            memory_by_size[size].append(avg_memory)
        
        avg_times = []
        avg_memories = []
        for size in sizes:
            if size in time_by_size:
                avg_times.append(np.mean(time_by_size[size]))
                avg_memories.append(np.mean(memory_by_size[size]))
        
        # Guardar datos para el comparativo
        all_time_data[algo] = avg_times
        all_memory_data[algo] = avg_memories
        
        # Gráfico individual (tiempo y memoria)
        plt.figure(figsize=(12, 6))
        plt.subplot(1, 2, 1)
        plt.plot(sizes[:len(avg_times)], avg_times, 'o-', color=colors[algo])
        plt.xscale('log')
        plt.yscale('log')
        plt.title(f"Tiempo - {algo}")
        plt.xlabel("Tamaño de datos")
        plt.ylabel("Tiempo (ms)")
        plt.grid(True)
        
        plt.subplot(1, 2, 2)
        plt.plot(sizes[:len(avg_memories)], avg_memories, 'o-', color=colors[algo])
        plt.xscale('log')
        plt.title(f"Memoria - {algo}")
        plt.xlabel("Tamaño de datos")
        plt.ylabel("Memoria (KB)")
        plt.grid(True)
        
        plt.tight_layout()
        plt.savefig(os.path.join(output_dir, f"scaling_{algo}.png"))
        plt.close()
    
    # Gráfico COMPARATIVO (todos los algoritmos juntos)
    plt.figure(figsize=(14, 6))
    
    # Subgráfico 1: Tiempo
    plt.subplot(1, 2, 1)
    for algo in algorithms:
        if all_time_data[algo]:
            plt.plot(sizes[:len(all_time_data[algo])], all_time_data[algo], 'o-', 
                    label=algo, color=colors[algo])
    plt.xscale('log')
    plt.yscale('log')
    plt.title("Comparación de tiempo (log-log)")
    plt.xlabel("Tamaño de datos")
    plt.ylabel("Tiempo (ms)")
    plt.legend()
    plt.grid(True)
    
    # Subgráfico 2: Memoria
    plt.subplot(1, 2, 2)
    for algo in algorithms:
        if all_memory_data[algo]:
            plt.plot(sizes[:len(all_memory_data[algo])], all_memory_data[algo], 'o-', 
                    label=algo, color=colors[algo])
    plt.xscale('log')
    plt.title("Comparación de memoria")
    plt.xlabel("Tamaño de datos")
    plt.ylabel("Memoria (KB)")
    plt.legend()
    plt.grid(True)
    
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, "scaling_comparison.png"))
    plt.close()

def main():
    input_file = "C:/Users/japoto/Desktop/INF221-2025-1-TAREA-1/code/sorting/data/measurements/bench.txt"
    output_dir = r'C:\Users\japoto\Desktop\INF221-2025-1-TAREA-1\code\sorting\data\plots'
    
    data = parse_benchmark_file(input_file)
    create_scaling_plots(data, output_dir)
    print(f"Gráficos guardados en: {output_dir}")

if __name__ == "__main__":
    main()