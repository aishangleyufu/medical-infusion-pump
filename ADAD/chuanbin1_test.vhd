
--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   23:26:28 08/09/2015
-- Design Name:   chuanbin1
-- Module Name:   C:/3130103382/ADAD/ADAD/chuanbin1_test.vhd
-- Project Name:  ADAD
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: chuanbin1
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

ENTITY chuanbin1_test_vhd IS
END chuanbin1_test_vhd;

ARCHITECTURE behavior OF chuanbin1_test_vhd IS 

	-- Component Declaration for the Unit Under Test (UUT)
	COMPONENT chuanbin1
	PORT(
		F50M : IN std_logic;
		din : IN std_logic;          
		pdate : OUT std_logic_vector(15 downto 0)
		);
	END COMPONENT;

	--Inputs
	SIGNAL F50M :  std_logic := '0';
	SIGNAL din :  std_logic := '0';

	--Outputs
	SIGNAL pdate :  std_logic_vector(15 downto 0);

BEGIN

	-- Instantiate the Unit Under Test (UUT)
	uut: chuanbin1 PORT MAP(
		F50M => F50M,
		din => din,
		pdate => pdate
	);

	tb : PROCESS
	BEGIN
		F50M<='1';wait for 5ns;
		F50M<='0';wait for 5ns;

	END PROCESS;

END;
