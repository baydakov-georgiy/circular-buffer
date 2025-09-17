import subprocess
import matplotlib.pyplot as plt

def run_test(push_type: int, n: int) -> float:
    """
    Запускает ./exectest push_type n и возвращает время работы в секундах.
    Ожидается, что программа печатает только число (время).
    """
    result = subprocess.run(
        ["./exectest", str(push_type), str(n)],
        capture_output=True,
        text=True,
        check=True
    )
    return float(result.stdout.strip())

def main():
    sizes = [10_000, 50_000, 100_000, 500_000, 1_000_000, 10_000_000]

    times_front = []
    times_back = []

    for n in sizes:
        t_front = run_test(1, n) * 1e9  # сек -> наносекунды
        t_back = run_test(0, n) * 1e9   # сек -> наносекунды
        times_front.append(t_front)
        times_back.append(t_back)
        print(f"n={n}: push_front={t_front:.0f} ns, push_back={t_back:.0f} ns")

    # Строим график
    plt.plot(sizes, times_front, marker="o", label="push_front")
    plt.plot(sizes, times_back, marker="o", label="push_back")

    plt.xlabel("Количество элементов")
    plt.ylabel("Время (наносекунды)")
    plt.title("Сравнение push_front и push_back")
    plt.legend()
    plt.grid(True)

    # Сохраняем график в файл
    plt.savefig("results.png", dpi=300)
    print("График сохранён в results.png")

if __name__ == "__main__":
    main()
