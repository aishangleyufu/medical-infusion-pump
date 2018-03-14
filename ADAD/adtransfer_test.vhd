
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   02:24:17 08/10/2015
-- Design Name:   adtransfer
-- Module Name:   C:/3130103382/ADAD/ADAD/adtransfer_test.vhd
-- Project Name:  ADAD
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: adtransfer
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

ENTITY adtransfer_test_vhd IS
END adtransfer_test_vhd;

ARCHITECTURE behavior OF adtransfer_test_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT adtransfer
	PORT(
		date : IN std_logic_vector(11 downto 0);          
		h3 : OUT std_logic_vector(3 downto 0);
		h2 : OUT std_logic_vector(3 downto 0);
		h1 : OUT std_logic_vector(3 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL date :  std_logic_vector(11 downto 0) := (others=>'0');

	--Outputs
	SIGNAL h3 :  std_logic_vector(3 downto 0);
	SIGNAL h2 :  std_logic_vector(3 downto 0);
	SIGNAL h1 :  std_logic_vector(3 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: adtransfer PORT MAP(
		date => date,
		h3 => h3,
		h2 => h2,
		h1 => h1
	);

	tb : PROCESS
	BEGIN
LP: for i in 0 to 4095 loop
date<=conv_std_logic_vector(i,12); --"001";
wait for 20ns;
end loop LP;
	END PROCESS;

END;
