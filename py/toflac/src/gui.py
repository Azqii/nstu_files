import tkinter as tk

from .syntax_analyzer import SyntaxAnalyzer
from .lexical_analyzer import LexicalAnalyzer


class GUI:
    def __init__(self, master: tk.Tk):
        self.master = master
        self.master.title("Анализатор декларации целых и комплексных чисел FORTRAN")
        self.master.geometry("1050x600")

        # Левая панель — ввод строки
        self.input_label = tk.Label(self.master, text="Введите строку:")
        self.input_label.pack(side="left", padx=10, pady=10)

        self.input_text = tk.Text(self.master, width=30, height=1)
        self.input_text.pack(side="left", padx=10, pady=10)

        self.parse_button = tk.Button(self.master, text="Анализировать", command=self.analyze)
        self.parse_button.pack(side="left", padx=10)

        # Правая панель — вывод результата
        self.output_frame = tk.Frame(self.master)
        self.output_frame.pack(side="right", padx=10, pady=10, fill="both", expand=True)

        self.output_label = tk.Label(self.output_frame, text="Результат анализа:")
        self.output_label.pack(anchor="w")

        self.output_text = tk.Text(self.output_frame, width=50, height=15, wrap="word", state='disabled')
        self.output_text.pack(fill="both", expand=True)

    def analyze(self):
        input_str = self.input_text.get("1.0", tk.END).strip()
        self.clear_output()

        try:
            # Шаг 1: Лексический анализ
            lexer = LexicalAnalyzer(input_str)
            tokens = lexer.tokenize()

            # Шаг 2: Синтаксический анализ
            parser = SyntaxAnalyzer(tokens)
            ast = parser.parse()

            # Вывод результатов
            self.insert_output("Токены:\n")
            for token in tokens:
                self.insert_output(f"{token}")

            self.insert_output("\nAST (абстрактное синтаксическое дерево):")
            self.insert_output(f"{ast}")
        except Exception as e:
            self.insert_output(f"❌ Ошибка: {e}")

    def insert_output(self, text: str):
        self.output_text.config(state='normal')
        self.output_text.insert(tk.END, text + "\n")
        self.output_text.config(state='disabled')

    def clear_output(self):
        self.output_text.config(state='normal')
        self.output_text.delete("1.0", tk.END)
        self.output_text.config(state='disabled')
