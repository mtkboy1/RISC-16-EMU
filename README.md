<h1> What is it?</h1>
This is a RISC-16 architecture emulator that includes some commands (see the list below)
<table>
          <tr>
              <td colspan="6"">Instructions ⬇️</td>
          </tr>
          <tr>
              <td>add</td>
              <td>R[regA] <- R[regB] + R[regC]</td>
          </tr>
          <tr>
              <td>addi</td>
              <td>R[regA] <- R[regB] + immed</td>
          </tr>
          <tr>
              <td>nand</td>
              <td>R[regA] <- ~(R[regB] & R[regC])</td>
          </tr>
          <tr>
              <td>lui</td>
              <td>R[regA] <- immed & 0xffc0</td>
          </tr>
          <tr>
              <td>sw</td>
              <td>R[regA] -> Mem[ R[regB] + immed ]</td>
          </tr>
          <tr>
              <td>lw</td>
              <td>R[regA] <- Mem[ R[regB] + immed ]</td>
          </tr>
          <tr>
              <td>beq</td>
              <td>if ( R[regA] == R[regB] ) {
                    PC <- PC + 1 + immed
                    (if label, PC <- label)
                    }</td>
                    </tr>
           <tr>
              <td>jalr</td>
              <td>PC <- R[regB], R[regA] <- PC + 1</td>
          </tr>
</table>
