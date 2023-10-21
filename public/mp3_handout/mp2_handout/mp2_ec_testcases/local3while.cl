-- Primary test for a while loop
-- computes fib(4)
-- result should be fib(4) = 5

class Main {
    main(): Int {
	let prev: Int <- 1 in			-- fib(0) = 1
	    let last: Int <- 1 in {		-- fib(1) = 1
	        (let i: Int <- 2 in
	             while (i <= 4) loop 
		         (let fibi: Int <- prev + last in {
			      prev <- last;
			      last <- fibi;
			      i <- i+1;
		          }) pool);
		last;
	    }
    };
};
