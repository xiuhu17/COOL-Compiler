-- Primary test for let-variables
-- computes "not(n = (n/2)*2)" == "not(n is even)"
-- result should be false for n even; true for n odd.

class Main {
    main(): Int {
	(let n: Int in {
	    n <- 15;					-- n  = 15 viz., odd
	    let b1: Bool, b2: Bool, b3: Bool in {
	 	b1 <- (n = (n/2)*2);			-- b1 = false
	        b2 <- not b1;				-- b2 = not b1 = true
	        b3 <- if (b1) then false else true fi;	-- b3 = not b1 = true
		if (b3) then 1 else 0 fi;		-- returns int(b3) = 1
	    };
         })
    };
};
