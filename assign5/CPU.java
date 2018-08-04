public class CPU implements Runnable {

	OS sim;
	String algorithm;
	int quantum;

	public CPU(OS sim, String alg, int q) {
		this.sim = sim;
		algorithm = alg;
		quantum = q;
	}

	@Override
	public void run() {

		PCB process = null;

		while (sim.CPUqueue.isEmpty()) {
			try {
				Thread.sleep(1);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		if (sim.debug)
			System.out.println("Starting " + algorithm);

		for (;;) {
			if (!sim.CPUqueue.isEmpty()) {

				switch (algorithm) {
					case "FIFO":
						/**
						 * Pick the first process
						 */

						synchronized (sim.CPUqueue) {
							process = sim.CPUqueue.remove(0);
						}

						burst(process);

						break;

					case "SJF":
						/**
						 * Pick the shortest burst time first
						 */

						synchronized (sim.CPUqueue) {
							process = sim.CPUqueue.get(0);

							for (PCB p : sim.CPUqueue) {
								if (p.CPUburst.get(0) < process.CPUburst.get(0)) {
									process = p;
								}
							}

							sim.CPUqueue.remove(process);
						}

						burst(process);

						break;

					case "PR":
						/**
						 * Pick the highest priority first
						 */

						synchronized (sim.CPUqueue) {
							process = sim.CPUqueue.get(0);

							for (PCB p : sim.CPUqueue) {
								if (p.priority > process.priority) {
									process = p;
								}
							}

							sim.CPUqueue.remove(process);
						}

						burst(process);

						break;

					case "RR":
						/**
						 * Pick the first process, and run it for quantum ms
						 */

						synchronized (sim.CPUqueue) {
							process = sim.CPUqueue.remove(0);
						}

						rrburst(process);

						break;
				}
			}
			if (sim.doneList.size() == sim.totalProcesses) {
				break;
			}
		}
	}

	private void burst(PCB process) {
		try {
			if (sim.debug)
				System.out.println("Begin CPU burst for " + process.CPUburst.get(0) + " ms for process " + process.id);
			Thread.sleep(process.CPUburst.get(0));
			if (sim.debug)
				System.out.println("Process " + process.id + " CPU burst concluded");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		process.turnaroundTime += process.CPUburst.get(0);
		process.cpuTime += process.CPUburst.get(0);

		synchronized (sim.CPUqueue) {
			for (PCB p : sim.CPUqueue) {
				p.waitingTime += process.CPUburst.get(0);
				p.turnaroundTime += process.CPUburst.get(0);
			}
		}

		process.CPUburst.remove(0);

		if (process.CPUburst.isEmpty()) {
			synchronized (sim.doneList) {
				if (sim.debug)
					System.out.println("Process " + process.id + " concluded");
				sim.doneList.add(process);
			}
		} else {
			synchronized (sim.IOqueue) {
				sim.IOqueue.add(process);
			}
		}
	}

	private void rrburst(PCB process) {
		int bursttime;
		int origburst = process.CPUburst.get(0);

		if (quantum < origburst) {
			bursttime = quantum;
			process.CPUburst.set(0, origburst - quantum);
		}
		else
			bursttime = origburst;

		try {
			if (sim.debug)
				System.out.println("Begin RR CPU burst for " + bursttime + " ms for process " + process.id);
			Thread.sleep(bursttime);
			if (sim.debug) {
				System.out.print("Process " + process.id + " RR CPU burst concluded");
				if (bursttime != origburst)
					System.out.println(", " + process.CPUburst.get(0) + " ms left in original burst");
				else
					System.out.println();
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		process.turnaroundTime += bursttime;
		process.cpuTime += bursttime;

		synchronized (sim.CPUqueue) {
			for (PCB p : sim.CPUqueue) {
				p.waitingTime += bursttime;
				p.turnaroundTime += bursttime;
			}
		}

		if (bursttime == origburst) {
			process.CPUburst.remove(0);
			if (sim.debug)
				System.out.println("Process " + process.id + " CPU burst concluded");
		}

		if (process.CPUburst.isEmpty()) {
			synchronized (sim.doneList) {
				sim.doneList.add(process);
				if (sim.debug)
					System.out.println("Process " + process.id + " concluded");
			}
		}
		else if (bursttime == origburst) {
			synchronized (sim.IOqueue) {
				sim.IOqueue.add(process);
			}
		}
		else {
			synchronized (sim.CPUqueue) {
				sim.CPUqueue.add(process);
			}
		}
	}
}
