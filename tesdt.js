function solve(protonsStart, neutronsStart, protonsTarget, neutronsTarget) {
	let op = [];
  
	// Calculate the difference between starting and target values for protons and neutrons
	let protonsDiff = protonsTarget - protonsStart;
	let neutronsDiff = neutronsTarget - neutronsStart;
  
	// Add or remove protons and neutrons based on the difference
	while (protonsDiff !== 0 || neutronsDiff !== 0) {
	  if (protonsDiff > 0 && neutronsDiff > 0 && protonsDiff % 2 === 0 && neutronsDiff % 2 === 0) {
		op.push("ALPHA");
		protonsDiff -= 2;
		neutronsDiff -= 2;
	  } else if (protonsDiff > 0) {
		op.push("PROTON");
		protonsDiff--;
	  } else if (neutronsDiff > 0) {
		op.push("NEUTRON");
		neutronsDiff--;
	  } else if (protonsDiff < 0) {
		op.push("POSITRON");
		protonsDiff++;
	  } else if (neutronsDiff < 0) {
		op.push("ANTI_NEUTRON");
		neutronsDiff++;
	  }
	}
  
	return op;
  }