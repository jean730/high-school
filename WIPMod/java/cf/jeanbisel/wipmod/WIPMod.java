package cf.jeanbisel.wipmod;

import net.minecraft.init.Blocks;
import net.minecraft.init.Items;
import net.minecraft.item.ItemStack;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.Mod.EventHandler;
import net.minecraftforge.fml.common.event.FMLInitializationEvent;
import net.minecraftforge.fml.common.event.FMLPreInitializationEvent;
import net.minecraftforge.fml.common.eventhandler.SubscribeEvent;
import net.minecraftforge.fml.common.registry.GameRegistry;
import net.minecraft.block.Block;
import net.minecraft.item.Item;
import net.minecraft.item.ItemBlock;
import net.minecraftforge.event.RegistryEvent;
import org.apache.logging.log4j.Logger;
import cf.jeanbisel.wipmod.blocks.*;
import net.minecraftforge.fml.common.SidedProxy;
import net.minecraft.client.renderer.block.model.ModelResourceLocation;
import net.minecraftforge.client.model.ModelLoader;
import net.minecraftforge.client.event.ModelRegistryEvent;
import net.minecraftforge.fml.relauncher.Side;
import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraft.world.DimensionType;
import net.minecraftforge.common.DimensionManager;
import net.minecraft.world.biome.Biome;
import cf.jeanbisel.wipmod.WIPBiome;


@Mod.EventBusSubscriber
@Mod(modid = WIPMod.MODID, name = WIPMod.NAME, version = WIPMod.VERSION)
public class WIPMod
{
    public static final String MODID = "wipmod";
    public static final String NAME = "WIP Mod";
    public static final String VERSION = "1.0";

    public static BlockTest blockTest = new BlockTest();
    public static Item ItemblockTest = new ItemBlock(blockTest).setRegistryName(blockTest.getRegistryName());
    public static WIPGrass WIPgrass = new WIPGrass();
    public static Item ItemWIPgrass = new ItemBlock(WIPgrass).setRegistryName(WIPgrass.getRegistryName());
    public static WIPDirt WIPdirt = new WIPDirt();
    public static Item ItemWIPdirt = new ItemBlock(WIPdirt).setRegistryName(WIPdirt.getRegistryName());
    public static WIPStone WIPstone = new WIPStone();
    public static Item ItemWIPstone = new ItemBlock(WIPstone).setRegistryName(WIPstone.getRegistryName());
    public static WIPBiome WIPbiome = new WIPBiome((new Biome.BiomeProperties("wipbiome")).setBaseHeight(1.0F).setHeightVariation(1.0F).setTemperature(0.2F).setRainfall(0.3F));

    private static Logger logger;

    @EventHandler
    public void preInit(FMLPreInitializationEvent event){
        logger = event.getModLog();
    }

    @SubscribeEvent
    @SideOnly(Side.CLIENT)
	public static void registerModels(ModelRegistryEvent event)
	{
        ModelLoader.setCustomModelResourceLocation(ItemblockTest,0,new ModelResourceLocation(ItemblockTest.getRegistryName().toString()));
        ModelLoader.setCustomModelResourceLocation(ItemWIPgrass,0,new ModelResourceLocation(ItemWIPgrass.getRegistryName().toString()));
        ModelLoader.setCustomModelResourceLocation(ItemWIPdirt,0,new ModelResourceLocation(ItemWIPdirt.getRegistryName().toString()));
        ModelLoader.setCustomModelResourceLocation(ItemWIPstone,0,new ModelResourceLocation(ItemWIPstone.getRegistryName().toString()));
    }

    @SubscribeEvent
    public static void registerBlocks(RegistryEvent.Register<Block> event) {
        event.getRegistry().registerAll(blockTest,WIPgrass,WIPdirt,WIPstone);
    }

    @SubscribeEvent
    public static void registerItems(RegistryEvent.Register<Item> event) {
        event.getRegistry().registerAll(ItemblockTest,ItemWIPgrass,ItemWIPdirt,ItemWIPstone);
    }
    @SubscribeEvent
    public void registerBiome(RegistryEvent.Register<Biome> event) {
        event.getRegistry().registerAll(WIPbiome);
    }

    @EventHandler
    public void init(FMLInitializationEvent event)
    {
        logger.info("Mod Initialized");
        DimensionType.register("wipworld","",2,WorldProviderWIP.class,false);
        DimensionManager.registerDimension( DimensionType.byName("wipworld").getId(), DimensionType.byName("wipworld"));
    }
}
