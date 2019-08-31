package cf.jeanbisel.wipmod.blocks;

import net.minecraft.block.Block;
import net.minecraft.block.material.Material;
import net.minecraft.creativetab.CreativeTabs;
import net.minecraft.util.math.BlockPos;
import net.minecraft.world.World;
import net.minecraft.util.EnumParticleTypes;
import net.minecraft.block.state.IBlockState;
import net.minecraft.entity.player.EntityPlayer;
import net.minecraft.util.EnumHand;
import net.minecraft.util.EnumFacing;
import net.minecraftforge.fml.relauncher.Side;
import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraft.block.SoundType;

public class WIPStone extends Block
{
    public WIPStone()
    {
        super(Material.ROCK);
        this.setRegistryName("wipmod:wipstone");
        this.setUnlocalizedName("wipmod.wipstone");
        this.setCreativeTab(CreativeTabs.BUILDING_BLOCKS);
		this.setHardness(1.5F);
		this.setResistance(10.0F);
		this.setSoundType(SoundType.STONE);
    }
}
