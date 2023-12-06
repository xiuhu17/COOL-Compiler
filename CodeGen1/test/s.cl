-- Simple test for the divide-by-0 check
-- Program should abort.

class Main {
    main(): Int {
	(let n: Int in {
	    n <- 3 * 3 + 1;	-- n = 10
	    let m: Int in {
	 	m <- (n*n) / n;	-- m = n = 10
	        m / (m - n);	-- m / 0 should cause program to abort
	    };
         })
    };
};

