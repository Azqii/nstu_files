namespace cs_lab2.Core.Models;

using Interfaces;

public class Seller : Employee, IMovable {
    public string ImagePath { get; set; } = "C:\\Users\\brone\\dev\\cs_lab2\\cs_lab2\\Static\\corner.png";
    public double X { get; set; }
    public double Y { get; set; }

    public Seller(
        string? name,
        int? age,
        int? experience,
        List<string>? positionsList,
        double x,
        double y
    ) : base(name, age, experience, positionsList) {
        X = x;
        Y = y;
    }

    public void Move() {
        X = (X += 10) % 350;
        Y = (Y += 10) % 450;
    }
}
