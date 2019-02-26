package main;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Welcome extends HttpServlet implements Servlet {
	private static final long serialVersionUID = 1L;
	private static int result;
	private REA_Hub myHub;
	private PrintWriter myObj;
	
	
    public Welcome()
    {
        super();
        System.out.println("This is Welcome class's constructor");
    }
    
    
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
	{
		/*
		 * Set the html syntax into play.*/
		response.setContentType("text/html");
		
		myObj = response.getWriter();
		
		String sensor1_data = request.getParameter("sensor1");
		String sensor2_data = request.getParameter("sensor2");
		String sensor3_data = request.getParameter("sensor3");
		
		myHub = new REA_Hub(sensor1_data, sensor2_data, sensor3_data, myObj);
		
		/*
		 * Let's compute which of these sensors is best working? There are three sensors: 1, 2 and 3. 
		 * If the sensorNum == 0 then none of the sensor's data should be stored*/
		result = myHub.getHighestPrioritySensor();
		
		myObj.println("<h2>Highest Priority Sensor is: "+result+" </h2>");
		myObj.println("<h3>Visit Main page: <a href=\"http://localhost:8080/R.E.A.S.N/SensorPage.html\">Visit R.E.A.S.N</a></h3>");
	}
}
