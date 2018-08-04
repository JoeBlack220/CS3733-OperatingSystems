import java.util.ArrayList;

public class PCB {

	int id;
	ArrayList<Integer> CPUburst;
	ArrayList<Integer> IOburst;
	int priority;
	int cpuTime, ioTime, turnaroundTime, waitingTime;

	public PCB(int id, String args[]) {
		this.id = id;
		CPUburst = new ArrayList<Integer>();
		IOburst = new ArrayList<Integer>();
		priority = Integer.parseInt(args[1]);
		cpuTime = 0;
		ioTime = 0;
		turnaroundTime = 0;
		waitingTime = 0;

		for (int x = 2; x < args.length; x++) {
			if (x % 2 == 0)
				CPUburst.add(Integer.parseInt(args[x]));
			else
				IOburst.add(Integer.parseInt(args[x]));
		}
	}

	public String toString() {
		return "Priority: " + priority + "\nCPU: " + CPUburst.toString() + "\nIO: " + IOburst.toString();
	}
}
