
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:38:23 08/09/2015
-- Design Name:   fenping2
-- Module Name:   C:/3130103382/ADAD/ADAD/fenping-test.vhd
-- Project Name:  ADAD
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: fenping2
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

ENTITY fenping-test_vhd IS
END fenping-test_vhd;

ARCHITECTURE behavior OF fenping-test_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT fenping2
	PORT(
		F50M : IN std_logic;          
		CS : OUT std_logic;
		SCLK : OUT std_logic
		);
	END COMPONENT;

	--Inputs
	SIGNAL F50M :  std_logic := '0';

	--Outputs
	SIGNAL CS :  std_logic;
	SIGNAL SCLK :  std_logic;

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: fenping2 PORT MAP(
		F50M => F50M,
		CS => CS,
		SCLK => SCLK
	);

	tb : PROCESS
	BEGIN

		F50M<='1';wait for 5ns;
		F50M<='0';wait for 5ns;
	END PROCESS;

END;
