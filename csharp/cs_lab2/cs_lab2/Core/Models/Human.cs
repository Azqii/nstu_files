namespace cs_lab2.Core.Models;

public class Human {
    protected string? Name { get; set; }
    protected int? Age { get; set; }

    public string GetBasicInfo() {
        return string.Format(
            "Имя: {0}, возраст: {1}", Name != null ? Name : "__", Age != null ? Age : "__"
        );
    }
}
