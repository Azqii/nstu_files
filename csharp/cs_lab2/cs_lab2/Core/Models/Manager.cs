namespace cs_lab2.Core.Models;

using Interfaces;

public class Manager : Employee, IMovable {
    public string ImagePath { get; set; } = "C:\\Users\\brone\\dev\\cs_lab2\\cs_lab2\\Static\\circle.png";
    private double CenterX { get; set; }
    private double CenterY { get; set; }
    private double Radius { get; set; }

    public double X { get; set; }
    public double Y { get; set; }
    private double Ctr { get; set; }

    public Manager(
        string? name,
        int? age,
        int? experience,
        List<string>? positionsList,
        double centerX,
        double centerY,
        double radius
    ) : base(name, age, experience, positionsList) {
        CenterX = centerX;
        CenterY = centerY;
        Radius = radius;
        Ctr = 0;
        Move();
    }

    public void Move() {
        if (Ctr.Equals(6.28)) {
            Ctr = 0;
        }

        X = Radius * Math.Cos(Ctr) + CenterX;
        Y = Radius * Math.Sin(Ctr) + CenterY;
        Ctr += 0.19625;
    }
}
