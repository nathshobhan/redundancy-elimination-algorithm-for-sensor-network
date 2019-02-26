package main;

import java.io.PrintWriter;
import java.util.HashMap;

public class REA_Hub
{
	private String sensor_data1;
	private String sensor_data2;
	private String sensor_data3;
	private PrintWriter printObj;
	
	public REA_Hub(String s1, String s2, String s3, PrintWriter printObj)
	{
		this.sensor_data1 = s1;
		this.sensor_data2 = s2;
		this.sensor_data3 = s3;
		
		this.printObj = printObj;
	}
	
	public int getHighestPrioritySensor()
	{
		printObj.println("<h2>Printing the Sensor's data set entered by the user.</h2>");
		
		int[] Sensor1_DataSet = getDataSet(sensor_data1, 1);
		double Sensor1_entropy = getEntropy(Sensor1_DataSet);
		printObj.println("<h3>Entropy of Sensor #1: "+Sensor1_entropy);

		printObj.println("<h2>----------------------------------------------------------------------------------------</h2>");
		
		int[] Sensor2_DataSet = getDataSet(sensor_data2, 2);
		double Sensor2_entropy = getEntropy(Sensor2_DataSet);
		printObj.println("<h3>Entropy of Sensor #2: "+Sensor2_entropy);

		printObj.println("<h2>----------------------------------------------------------------------------------------</h2>");

		int[] Sensor3_DataSet = getDataSet(sensor_data3, 3);
		double Sensor3_entropy = getEntropy(Sensor3_DataSet);
		printObj.println("<h3>Entropy of Sensor #3: "+Sensor3_entropy);

		printObj.println("<h2>----------------------------------------------------------------------------------------</h2>");
		
		if(Sensor1_entropy>Sensor2_entropy&&Sensor1_entropy>Sensor3_entropy)
			return 1;
		else if(Sensor2_entropy>Sensor1_entropy&&Sensor2_entropy>Sensor3_entropy)
			return 2;
		else if(Sensor3_entropy>Sensor1_entropy&&Sensor3_entropy>Sensor2_entropy)
			return 3;
		else
			return 0;
	}
	
	private double getEntropy(int[] ar)
	{
		/*
		 * Step 1: Creating the Hash map and corresponding key-value pairs*/
		int[][] matrix = getHash(ar);
		
		//let's print this matrix
		printObj.println("<h3>Hash Map: Key Value Pair for Each data entry with frequency</h3>");
		for(int i = 0;i<matrix.length;i++)
		{
			printObj.println("<p>Entry: "+matrix[i][0]+" --> Frequency: "+matrix[i][1]+"</p>");
		}
		
		/*
		 * Step 2: Find probability of each entrySet*/
		double[] probAr = getProb(matrix);
		
		printObj.println("<h3>Individual Probability of Each data entry.</h3>");
		for(int i = 0;i<probAr.length;i++)
		{
			printObj.println("<p>Entry: "+matrix[i][0]+" --> Frequency: "+matrix[i][1]+" == Probability: "+probAr[i]+"</p>");
		}
		printObj.println("<h3>Total Probability = 1</h3>");
		
		double[] invProbAr = getInverseProb(probAr);
		
		double[] logProbAr = getLogOfInvProb(invProbAr);
		
		double entropy = 0;
		
		for(int i = 0;i<probAr.length;i++)
			entropy += probAr[i]*logProbAr[i];
		
		return entropy;
	}
	
	private double[] getLogOfInvProb(double[] ar)
	{
		double[] temp = new double[ar.length];
		
		for(int i = 0;i<ar.length;i++)
		{
			temp[i] = Math.log(ar[i])/Math.log(2);
		}
		
		return temp;
	}
	
	private double[] getInverseProb(double[] ar)
	{
		double[] temp = new double[ar.length];
		
		for(int i = 0;i<ar.length;i++)
		{
			temp[i] = 1/ar[i];
		}
		
		return temp;
	}
	
	private double[] getProb(int[][] matrix)
	{
		double[] tempProb = new double[matrix.length];
		
		double totalMessage = 0;
		
		for(int i = 0;i<matrix.length;i++)
			totalMessage += matrix[i][1];
		
		for(int i = 0;i<tempProb.length;i++)
			tempProb[i] = matrix[i][1]/totalMessage;
		
		return tempProb;
	}
	
	/*
	 * this method returns the matrix of key-value pair for each dataset
	 * Here key is each of the data set entry
	 * Here value is the frequency of the corresponding key*/
	private int[][] getHash(int[] ar)
	{
		HashMap<Integer, Integer> myHash = new HashMap<Integer, Integer>();
		
		for(int i = 0;i<ar.length;i++)
		{
			if(myHash.containsKey(ar[i])==true)
				myHash.replace(ar[i], myHash.get(ar[i])+1);
			else
				myHash.put(ar[i], 1);
		}
		
		int[][] matrix = new int[ar.length][2];
		int matrixIndex = 0;
		
		for(int key: myHash.keySet())
		{
			matrix[matrixIndex][0] = key;
			matrix[matrixIndex][1] = myHash.get(key);
			matrixIndex++;
		}
		
		int[][] finalMatrix = new int[matrixIndex][2];
		
		for(int i = 0;i<matrixIndex;i++)
		{
			finalMatrix[i][0] = matrix[i][0];
			finalMatrix[i][1] = matrix[i][1];
		}
		
		return finalMatrix;
	}
	
	private int[] getDataSet(String s, int num)
	{
		printObj.println("<h3>Sensor "+num+"# Dataset: "+s+"</h3>");
		
		String[] tempStrAr = s.split("-");
		
		int[] tempIntAr = new int[tempStrAr.length];
		
		printObj.println("Data Set in Integer: ");
		for(int i = 0;i<tempIntAr.length;i++)
		{
			tempIntAr[i] = Integer.parseInt(tempStrAr[i]);
			printObj.print(tempIntAr[i]+" ");
		}
		
		printObj.println();  //simple new line command
		
		return tempIntAr;
	}
}
