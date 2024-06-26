namespace cs_lab3.Controllers;

using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Models;

[Route("api/[controller]")]
[ApiController]
public class EmployeesController : ControllerBase {
    private readonly EmployeeContext _context;

    public EmployeesController(EmployeeContext context) {
        _context = context;
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<Employee>>> GetEmployees(string? name) {
        return await _context.Employees.Where(employee => name == null || employee.Name == name).ToListAsync();
    }

    [HttpGet("{id}")]
    public async Task<ActionResult<Employee>> GetEmployee(long id) {
        var employee = await _context.Employees.FindAsync(id);

        if (employee == null) {
            return NotFound();
        }

        return employee;
    }

    [HttpPut("{id}")]
    public async Task<IActionResult> PutEmployee(long id, Employee employee) {
        if (id != employee.Id) {
            return BadRequest();
        }

        _context.Entry(employee).State = EntityState.Modified;

        try {
            await _context.SaveChangesAsync();
        }
        catch (DbUpdateConcurrencyException) {
            if (!EmployeeExists(id)) {
                return NotFound();
            }
            throw;
        }

        return CreatedAtAction("GetEmployee", new { id = employee.Id }, employee);
    }

    [HttpPost]
    public async Task<ActionResult<Employee>> PostEmployee(Employee employee) {
        _context.Employees.Add(employee);
        await _context.SaveChangesAsync();

        return CreatedAtAction("GetEmployee", new { id = employee.Id }, employee);
    }

    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteEmployee(long id) {
        var employee = await _context.Employees.FindAsync(id);
        if (employee == null) {
            return NotFound();
        }

        _context.Employees.Remove(employee);
        await _context.SaveChangesAsync();

        return NoContent();
    }

    private bool EmployeeExists(long id) {
        return _context.Employees.Any(e => e.Id == id);
    }
}
