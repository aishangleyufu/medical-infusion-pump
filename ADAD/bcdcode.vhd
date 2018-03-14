----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:49:52 07/27/2015 
-- Design Name: 
-- Module Name:    bcdcode - Behavioral 
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

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity bcdcode is
    Port ( d : in  STD_LOGIC_VECTOR (3 downto 0);
           bcd_code : out  STD_LOGIC_VECTOR (6 downto 0));
end bcdcode;

architecture Behavioral of bcdcode is

begin
process(d)
begin
case d IS
WHEN "0000"=>bcd_code<="0000001";
WHEN "0001"=>bcd_code<="1001111";
WHEN "0010"=>bcd_code<="0010010";
WHEN "0011"=>bcd_code<="0000110";
WHEN "0100"=>bcd_code<="1001100";
WHEN "0101"=>bcd_code<="0100100";
WHEN "0110"=>bcd_code<="0100000";
WHEN "0111"=>bcd_code<="0001111";
WHEN "1000"=>bcd_code<="0000000";
WHEN "1001"=>bcd_code<="0000100";
WHEN OTHERS=>bcd_code<="1111111";
END CASE;
END PROCESS;
END Behavioral;

