using Microsoft.AspNetCore.Mvc;
using System; // we need DateTime
using System.Collections.Concurrent; // need for ConcurrentDictionary

namespace C2Server.Controllers
{
    [ApiController] // Enables API specific features like automatic model validation (e.g returns 400 for invalid json)
    [Route("api/[controller]")] // Indicates the endpoint of the controller, here, the `Controller`suffix will be deleted so the endpoint is /api/Agent
    public class AgentController : ControllerBase // Inheriting from ControllerBase for Web API functionality (no UI related features like Controller)
    {

        // declaring a static ConcurrentDictionary to store agent check-ins, mapping AgentId (string) to Timestamp (Datetime)
        // ConcurrentDictionary ensures thread-safety for multiple agents beaconing simulatenously
        private static readonly ConcurrentDictionary<string, DateTime> AgentRegistry = new(); // thread-safe dictionary with key value pairs, 

        [HttpPost] // we're specifying that the following method handles POST request to /api/Agent
        public IActionResult PostAgent([FromBody] AgentRequest request)
// IActionResult is an interface that provides a flexible and consistent way of handling requests
        {
            if (request == null || string.IsNullOrEmpty(request.AgentId))
            {
                return BadRequest("Invalid or missing AgentID");
            }

            AgentRegistry[request.AgentId] = request.Timestamp;
// Returning a 200 OK response, using new to create an anonymous type in C#, a temporary object. OK() wraps the object in a HTTP 200 OK response and serialize it to JSON
            return Ok(new { Status = "OK", Message = "Agent received" });
        }

        public class AgentRequest
        {
            public required string AgentId { get; set; }
            public DateTime Timestamp { get; set; }
        }

    }
}
