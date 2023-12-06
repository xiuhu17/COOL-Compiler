-- Primary test for let-variables
-- computes (n*n + n) / n for constant n = 16
-- result should be n+1 = 11

class Main {
    main(): Int {
	(let n: Int in {
	    n <- 3 * 3 + 1;	-- n = 10
	    let m: Int in {
	 	m <- n*n + n;	-- m = 110
	        m / n;		-- result should be n+1 = 11
	    };
         })
    };
};
