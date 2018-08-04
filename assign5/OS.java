import java.util.ArrayList;

public class OS {

	public ArrayList<PCB> CPUqueue;
	public ArrayList<PCB> IOqueue;
	public ArrayList<PCB> doneList;
	public volatile int totalProcesses;
	public boolean debug;

	public OS(ArrayList<PCB> cpuq, ArrayList<PCB> ioq, ArrayList<PCB> dl, int tp, boolean db) {
		CPUqueue = cpuq;
		IOqueue = ioq;
		doneList = dl;
		totalProcesses = tp;
		debug = db;
	}
}
