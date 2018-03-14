
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   19:29:01 07/27/2015
-- Design Name:   bcdcode
-- Module Name:   C:/3130103382/ADAD/ADAD/bcdcode-test.vhd
-- Project Name:  ADAD
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: bcdcode
--
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends 
-- that these types always be used for the top-level I/O of a design in order 
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;
USE ieee.std_logic_arith.all;

ENTITY bcdcode-test_vhd IS
END bcdcode-test_vhd;

ARCHITECTURE behavior OF bcdcode-test_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT bcdcode
	PORT(
		d : IN std_logic_vector(3 downto 0);          
		bcd_code : OUT std_logic_vector(6 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL d :  std_logic_vector(3 downto 0) := (others=>'0');

	--Outputs
	SIGNAL bcd_code :  std_logic_vector(6 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: bcdcode PORT MAP(
		d => d,
		bcd_code => bcd_code
	);

	tb : PROCESS
	BEGIN
      LP: for i in 0 to 15 loop
          d<=conv_std_logic_vector(i,4); --"001"; 
          wait for 20ns;
          end loop LP;	
			 -- Wait 100 ns for global reset to finish
----		wait for 100 ns;

		-- Place stimulus here

----		wait; -- will wait forever
	END PROCESS;

END;
