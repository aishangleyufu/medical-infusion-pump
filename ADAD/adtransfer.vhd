----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    02:15:44 08/10/2015 
-- Design Name: 
-- Module Name:    adtransfer - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
USE ieee.std_logic_arith.all;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity adtransfer is
    Port (  date: in STD_LOGIC_VECTOR (11 downto 0);
     	     h3 : out  STD_LOGIC_VECTOR (3 downto 0);
           h2 : out  STD_LOGIC_VECTOR (3 downto 0);
           h1 : out  STD_LOGIC_VECTOR (3 downto 0);
			  B: INOUT INTEGER RANGE 0 TO 4095);
end adtransfer;

architecture Behavioral of adtransfer is
SIGNAL d: STD_LOGIC_VECTOR(11 downto 0);
begin
process(date)

variable p:integer range 0 to 330;
variable l3:integer range 0 to 3;
variable l2:integer range 0 to 10;
variable l1:integer range 0 to 20;
begin
B<=CONV_INTEGER(date);
p:=B*330/4096;
l3:=p*10/1024;
l2:=(p-100*l3)*102/1024;
l1:=p-100*l3-10*l2;
h3<=conv_std_logic_vector(l3,4);
h2<=conv_std_logic_vector(l2,4);
h1<=conv_std_logic_vector(l1,4);
end process;
end Behavioral;

