import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class FileRead implements Runnable {

	BufferedReader in;
	OS sim;

	public FileRead(String fn, OS sim) {
		try {
			FileReader fr = new FileReader(fn);
			in = new BufferedReader(fr);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		this.sim = sim;
	}

	@Override
	public void run() {
		String line = "";
		String parsed[];

		try {
			while ((line = in.readLine()) != null) {
				line = line.trim();
				parsed = line.split("\\s+");

				switch (parsed[0]) {
					case "proc" :
						PCB block = new PCB(sim.totalProcesses, parsed);
						sim.totalProcesses++;
						sim.CPUqueue.add(block);
						break;
					case "sleep" :
						Thread.sleep(Integer.parseInt(parsed[1]));
						break;
					case "stop" :
						return;
					default :
						System.err.println("Fatal error reading from file!");
						System.exit(2);
				}
			}
		} catch (IOException | NumberFormatException | InterruptedException e) {
			e.printStackTrace();
		}
	}
}
