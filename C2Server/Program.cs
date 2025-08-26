var builder = WebApplication.CreateBuilder(args);

// Registers MVC controller support in the DI container, enabling the use of controller classes to handle HTTP requests
builder.Services.AddControllers();
// Registering OpenAPI swagger support, which generates interactive API documentation page to test endpoints.
builder.Services.AddOpenApi();

// Builds the WebApplication object from the configured builder.
var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.MapOpenApi();
}

app.UseHttpsRedirection();
app.MapControllers();

app.Run();
