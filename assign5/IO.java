public class IO implements Runnable {

	OS sim;

	public IO(OS sim) {
		this.sim = sim;
	}

	@Override
	public void run() {
		PCB process = null;

		while (sim.IOqueue.isEmpty()) {
			try {
				Thread.sleep(1);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		for (;;) {

			if (!sim.IOqueue.isEmpty()) {

				synchronized (sim.IOqueue) {
					process = sim.IOqueue.remove(0);
				}

				try {
					if (sim.debug)
						System.out.println("Begin IO burst for " + process.IOburst.get(0) + " ms for process " + process.id);
					Thread.sleep(process.IOburst.get(0));
					if (sim.debug)
						System.out.println("Process " + process.id + " IO burst concluded");
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

				process.turnaroundTime += process.IOburst.get(0);
				process.ioTime += process.IOburst.get(0);

				synchronized (sim.IOqueue) {
					for (PCB p : sim.IOqueue) {
						p.waitingTime += process.IOburst.get(0);
						p.turnaroundTime += process.IOburst.get(0);
					}

				}

				process.IOburst.remove(0);

				synchronized (sim.CPUqueue) {
					sim.CPUqueue.add(process);
				}
			}
			if (sim.doneList.size() == sim.totalProcesses) {
				break;
			}
		}
	}
}
