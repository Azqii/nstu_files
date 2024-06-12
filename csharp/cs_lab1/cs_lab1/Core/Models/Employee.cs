namespace cs_lab1.Core.Models;

using Interfaces;

public class Employee : Human, IStringable {
    private int? Experience { get; set; }
    private List<string>? PositionsList { get; set; }

    public Employee(string? name, int? age, int? experience, List<string>? positionsList) {
        Name = name;
        Age = age;
        Experience = experience;
        PositionsList = positionsList;
    }

    public string GetAsString() {
        return string.Format(
            "{0}, {1}, Опыт: {2}, Список должностей: {3}",
            Name != null ? Name : "__",
            Age != null ? Age : "__",
            Experience != null ? Experience : "__",
            PositionsList != null ? string.Join(", ", PositionsList) : "__"
        );
    }
}
