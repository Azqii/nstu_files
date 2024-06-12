namespace cs_lab1.Core.Exceptions;

public class EmptyNameException : Exception {
    public EmptyNameException(string message) : base(message) {}
}
