using System.Windows;

namespace cs_lab1;

using Core.Exceptions;
using Core.Models;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window {
    private List<Employee> EmployeesList { get; set; } = [];

    public MainWindow() {
        InitializeComponent();
    }

    private void AddEmployee(object sender, RoutedEventArgs args) {
        try {
            var name = NameInput.Text;
            if (name == "") {
                throw new EmptyNameException("У служащего должно быть имя!");
            }

            var employee = new Employee(
                name,
                AgeInput.Text == "" ? null : Int32.Parse(AgeInput.Text),
                ExperienceInput.Text == "" ? null : Int32.Parse(ExperienceInput.Text),
                PositionsInput.Text.Split().ToList()
            );

            EmployeesList.Add(employee);
            // Employees.Items.Add(employee.GetAsString());
            RefillEmployeesListBox();
        }
        catch (Exception exception) {
            MessageBox.Show($"Ошибка: {exception.Message}");
        }
    }

    private void DeleteEmployee(object sender, RoutedEventArgs args) {
        if (Employees.SelectedItems.Count == 1) {
            var index = Employees.SelectedIndex;

            EmployeesList.RemoveAt(index);
            // Employees.Items.RemoveAt(index);
            RefillEmployeesListBox();
        }
    }

    private void RefillEmployeesListBox() {
        Employees.Items.Clear();
        foreach (var employee in EmployeesList) {
            Employees.Items.Add(employee.GetAsString());
        }
    }
}
