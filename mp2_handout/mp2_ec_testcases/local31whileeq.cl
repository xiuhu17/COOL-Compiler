-- Primary test for a while loop with the '=' operator
-- computes fib(2)
-- result should be fib(2) = 2

class Main {
    main(): Int {
	let prev: Int <- 1 in			-- fib(0) = 1
	    let last: Int <- 1 in {		-- fib(1) = 1
	        (let i: Int <- 2 in
	             while (i = 2) loop 
		         (let fibi: Int <- prev + last in {
			      prev <- last;
			      last <- fibi;
			      i <- i+1;
		          }) pool);
		last;
	    }
    };
};
