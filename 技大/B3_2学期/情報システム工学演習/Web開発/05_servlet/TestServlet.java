import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet( urlPatterns = { “/TestServlet” } )
public class TestServlet extends HttpServlet {
  protected void doGet(HttpServletRequest req, HttpServletResponse resp)
    throws ServletException, IOException {
      doMain(req,resp);
    }
    protected void doPost(HttpServletRequest req, HttpServletResponse resp)
    throws ServletException, IOException {
      doMain(req,resp);
    }
  protected void doMain(HttpServletRequest req, HttpServletResponse resp)
  throws ServletException, IOException {
  req.setCharacterEncoding("UTF-8");
  resp.setContentType("text/html; charset=UTF-8");
    
  }
}