import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class assign5 {
	public static void main(String args[]) {
		ExecutorService application = Executors.newCachedThreadPool();
		ArrayList<PCB> CPUqueue = new ArrayList<PCB>();
		ArrayList<PCB> IOqueue = new ArrayList<PCB>();
		ArrayList<PCB> doneList = new ArrayList<PCB>();
		int totalProcesses = 0;

		StackTraceElement[] stack = Thread.currentThread ().getStackTrace ();
	    StackTraceElement main = stack[stack.length - 1];

	    if (args.length < 4 || args.length > 7) {
			sys_err("Invalid arguments", main);
		}

		String algorithm = null;
		String fileName = null;
		int quantum = -1;
		boolean debug = false;

		for (int i = 0; i < args.length; i++) {
			switch (args[i]) {
			case "-alg":
				if (i + 1 == args.length) {
					sys_err("No algorithm specified. Options: [FIFO|SJF|PR|RR]", main);
				}
				algorithm = args[i + 1];
				i++;
				break;
			case "-input":
				if (i + 1 == args.length) {
					sys_err("No input file name specified", main);
				}
				fileName = args[i + 1];
				i++;
				break;
			case "-quantum":
				if (i + 1 == args.length) {
					sys_err("No quantum time specified", main);
				}
				try {
					quantum = Integer.parseInt(args[i + 1]);
				} catch (NumberFormatException e) {
					sys_err("Quantum must be an integer in milliseconds", main);
				}
				i++;
				break;
			case "-debug":
				System.out.println("Debugging set");
				debug = true;
				break;
			default:
				sys_err("Invalid arguments", main);
			}
		}

		if (algorithm == null) {
			sys_err("Algorithm flag is required", main);
		}

		if (fileName == null) {
			sys_err("Input flag is required", main);
		}

		if (algorithm.equals("RR") && quantum < 1) {
			sys_err("Quantum flag is required for RR", main);
		}

		OS sim = new OS(CPUqueue, IOqueue, doneList, totalProcesses, debug);

		application.execute(new FileRead(fileName, sim));
		application.execute(new CPU(sim, algorithm, quantum));
		application.execute(new IO(sim));

		application.shutdown();

		try {
			application.awaitTermination(1, TimeUnit.MINUTES);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		int numprocs = 0;
		int totalCPU = 0;
		int totalTurn = 0;
		int totalWait = 0;

		for (PCB p : doneList) {
			numprocs++;
			totalCPU += p.cpuTime;
			totalTurn += p.turnaroundTime;
			totalWait += p.waitingTime;
		}

		double util = roundTwoDecimals(((double)totalCPU / totalTurn) * 100);
		double averageTurn = roundTwoDecimals((double)totalTurn / numprocs);
		double throughput = roundTwoDecimals((1000 / averageTurn));
		double averageWait = roundTwoDecimals((double)totalWait / numprocs);

		System.out.println("Input File Name    : " + fileName);
		System.out.print("CPU Schedule Alg   : " + algorithm);
		if (algorithm.equals("RR"))
			System.out.println(" " + quantum);
		else
			System.out.println();
		System.out.println("CPU utilization    : " + util + "%");
		System.out.println("Throughput         : " + throughput + " processes per second");
		System.out.println("Turnaround time    : " + averageTurn + " ms (average) " + totalTurn + " (total)");
		System.out.println("Waiting time       : " + averageWait + " ms (average) " + totalWait + " (total)");
	}

	public static void sys_err(String message, StackTraceElement main) {
		System.err.println(message);
		System.err.println("Usage: java " + main.getClassName() + " -alg [FIFO|SJF|PR|RR] [-quantum [integer(ms)]] -input [file name]");
		System.exit(1);
	}

	public static double roundTwoDecimals(double d) {
		DecimalFormat twoDForm = new DecimalFormat("#.##");
		return Double.valueOf(twoDForm.format(d));
	}
}
