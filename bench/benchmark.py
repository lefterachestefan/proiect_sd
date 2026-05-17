import subprocess
import os

algos = [
    "bubble",
    "insertion",
    "gnome",
    "heap",
    "merge",
    "quick",
    "intro",
    "patience",
    "radix",
    "std::sort",
]
test_sizes = [20000, 10000000]
test_types = ["random", "sorted", "reverse", "nearly_sorted"]


def run_benchmark():
    raw_results = []
    std_sort_times = {}  # key: (size, type), value: time

    if not os.path.exists("tests"):
        os.makedirs("tests")

    for size in test_sizes:
        for t_type in test_types:
            test_file = f"tests/test_{size}_{t_type}.txt"
            if not os.path.exists(test_file):
                print(f"Generating {test_file}...")
                with open(test_file, "w") as f:
                    subprocess.run(
                        ["luau", "bench/generator.luau", "-a", str(size), t_type],
                        stdout=f,
                    )

            for algo in algos:
                if size > 20000 and algo in ["bubble", "insertion", "gnome"]:
                    continue

                print(f"Running {algo} on {test_file}...")
                env = os.environ.copy()
                env["ALGO"] = algo

                try:
                    timeout = 300 if size <= 20000 else 60
                    result = subprocess.run(
                        ["./build/sorter"],
                        input=open(test_file, "rb").read(),
                        env=env,
                        capture_output=True,
                        timeout=timeout,
                    )

                    if result.returncode == 0:
                        duration = float(result.stderr.decode().strip())
                        raw_results.append(
                            {
                                "algo": algo,
                                "size": size,
                                "type": t_type,
                                "time": duration,
                            }
                        )
                        if algo == "std::sort":
                            std_sort_times[(size, t_type)] = duration
                        print(f"  Result: {duration}s")
                    else:
                        print(f"  Error: {result.stderr.decode()}")
                except subprocess.TimeoutExpired:
                    print("  Timeout!")
                    raw_results.append(
                        {"algo": algo, "size": size, "type": t_type, "time": "TIMEOUT"}
                    )
                except Exception as e:
                    print(f"  Failed: {e}")

    with open("benchmark_results.csv", "w") as f:
        f.write("Algorithm,Size,Type,Time(s),% vs std::sort\n")
        for res in raw_results:
            comparison = ""
            if res["time"] != "TIMEOUT":
                std_time = std_sort_times.get((res["size"], res["type"]))
                if std_time and std_time > 0:
                    # compared to std::sort
                    # +% => slower, -% => faster
                    diff_pct = (res["time"] - std_time) / std_time * 100
                    comparison = f"{diff_pct:+.2f}%"
                elif res["algo"] == "std::sort":
                    comparison = "0.00%"
            else:
                comparison = "N/A"

            f.write(
                f"{res['algo']},{res['size']},{res['type']},{res['time']},{comparison}\n"
            )


if __name__ == "__main__":
    run_benchmark()
